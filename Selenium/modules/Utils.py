import time 
import pyautogui
import os
import json
from selenium.webdriver.chrome.service import Service
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.common.alert import Alert
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException

def click_specific_hyperlink_in_email(driver, method="index", value=0):
    try:
        # Switch to iframe where the email content is displayed
        iframe_element = WebDriverWait(driver, 5).until(
            EC.presence_of_element_located((By.XPATH, '//iframe[contains(@id,"main_MSGC")]'))
        )
        driver.switch_to.frame(iframe_element)

        print("Waiting for hyperlinks to be available...")
        
        # Using XPath to find all hyperlink elements
        hyperlinks = WebDriverWait(driver, 5).until(
            EC.presence_of_all_elements_located((By.XPATH, '//span[@class="Object" and @role="link"]/a'))
        )
        
        if not hyperlinks:
            print("No hyperlinks found.")
            return
        
        target_link = None
        
        if method == "index":
            target_link = hyperlinks[value]
        elif method == "attribute":
            for link in hyperlinks:
                if link.get_attribute('href') == value:
                    target_link = link
                    break
        elif method == "text":
            for link in hyperlinks:
                if link.text == value:
                    target_link = link
                    break
                    
        if target_link:
            print(f"Clicking hyperlink with text: {target_link.text}")
            target_link.click()
            # Wait 10 seconds to allow the new tab to be opened
            time.sleep(10)
        else:
            print("No matching hyperlink found.")

        # Switch back to the default content
        driver.switch_to.default_content()

    except TimeoutException as ex:
        print("Could not find any hyperlink. Exception:", ex)

def wait_for_element(driver, timeout, by, value):
    return WebDriverWait(driver, timeout).until(EC.presence_of_element_located((by, value)))

def click_any_attachment_download(driver, download_option="all", index_values=[]):
    try:
        print("Waiting for attachment div to be available...")
        attachment_div = WebDriverWait(driver, 5).until(
            EC.presence_of_element_located((By.XPATH, '//div[contains(@id,"zv__CLV__main_MSGC")]'))
        )

        dynamic_id_part = attachment_div.get_attribute('id').split('zv__CLV__main_MSGC')[-1].split('_attLinks')[0]
        
        print(f"Dynamic ID part: {dynamic_id_part}")
        
        if download_option == "all":
            # download_all_button = attachment_div.find_element(By.XPATH, f'.//a[contains(@id, "main_MSGC{dynamic_id_part}_attLinks_{index}_download")]')
            # download_all_button = attachment_div.find_element(By.XPATH, f'.//a[contains(@id, "main_MSGC{dynamic_id_part}_attLinks_download")]')
            download_all_button = attachment_div.find_element(By.XPATH, f'.//a[contains(@id, "main_MSGC{dynamic_id_part}_downloadAll")]')
            download_all_button.click()
            time.sleep(10)
            return

        attachment_files = attachment_div.find_elements(By.XPATH, './/a[@class="AttLink"]')

        if not attachment_files:
            print("No attachments found.")
            return

        if download_option == "index":
            for index in index_values:
                target_file = attachment_div.find_element(By.XPATH, f'.//a[contains(@id, "main_MSGC{dynamic_id_part}_attLinks_{index}_download")]')
                target_file.click()
                time.sleep(10)
                
    except TimeoutException as ex:
        print("Could not find the attachment or download button. Exception:", ex)

def click_allow_on_popup(driver):
    try:
        # Wait for the popup to appear
        WebDriverWait(driver, 5).until(EC.alert_is_present())

        # Accept the alert (popup)
        Alert(driver).accept()
    except TimeoutException:
        print("No alert appeared.")

def find_and_process_new_email(driver, download_option="all", index_values=[]):
    while True:
        try:
            # Check if there are unread emails or not
            all_rows = driver.find_elements(By.CSS_SELECTOR, '[id^="zli__CLV-main__"]')
            unread_found = False
            
            for row in all_rows:
                if 'Unread' in row.find_element(By.CLASS_NAME, 'ZmRowDoubleHeader').get_attribute('class'):
                    row.click()
                    unread_found = True
                    click_any_attachment_download(driver, download_option, index_values)  
                    break
            
            if not unread_found:
                # Click the reload button if there are no unread emails
                reload_button = driver.find_element(By.ID, "CHECK_MAIL")
                reload_button.click()
            
            # Click on the Inbox button
            inbox_button = driver.find_element(By.ID, "zti__main_Mail__2_textCell")
            inbox_button.click()

            # Click on the Reload button
            time.sleep(1)
            reload_button = driver.find_element(By.ID, "CHECK_MAIL")
            reload_button.click()
            # Scroll down to load more emails
            # driver.find_element(By.TAG_NAME, 'body').send_keys(Keys.PAGE_DOWN)
            
        except Exception as e:
            print(f"An error occurred: {e}")
            time.sleep(30)


def open_config_file(json_file):
    with open(json_file, 'r') as f:
        return json.load(f)
    

def perform_action(func, close=True, *args, **kwargs):
    driver = init_driver()
    login(driver)
    time.sleep(5)
    func(driver, *args, **kwargs)
    time.sleep(5)
    if close:
        logout(driver)
        time.sleep(5)
        close_program(driver)