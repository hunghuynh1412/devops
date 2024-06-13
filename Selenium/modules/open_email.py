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
from modules.Utils import *

def open_email_by_subject(driver, subject, tag=""):
    email = WebDriverWait(driver, 5).until(EC.presence_of_element_located((By.XPATH, "//span[contains(text(), '%s')]" % (subject))))
    email.click()
    time.sleep(5)
    # Click on first hyperlink
    if tag in ("hyperlink"):
        click_specific_hyperlink_in_email(driver)
        return
    # Click on first file download
    if tag in ("download"):
        #############################
        attachment_div = WebDriverWait(driver, 5).until(
            EC.presence_of_element_located((By.XPATH, '//div[contains(@id,"zv__CLV__main_MSGC")]'))
        )
        # find id of message in mail
        dynamic_id_part = attachment_div.get_attribute('id').split('zv__CLV__main_MSGC')[-1].split('_attLinks')[0] 
        # check_id = attachment_div.get_attribute('id')
        # print(attachment_div.find_element(By.XPATH, f'.//a[contains(@id, "main_MSGC{dynamic_id_part}_downloadAll")]'))  
        print(f"Dynamic ID part: {dynamic_id_part}")              
        # get all attachment in message
        attachLink = driver.find_elements(By.CSS_SELECTOR, 'a.AttLink')
        # find message have button download all
        for index in attachLink:
            if f'main_MSGC{dynamic_id_part}_downloadAll' in index.get_attribute('id'):
                click_any_attachment_download(driver,download_option="all", index_values=[])
                return
        # if can't file button download all, just download first attachment in message
        click_any_attachment_download(driver,download_option="index", index_values=[2])
        return
        
    # click_allow_on_popup(driver)

def open_newest_email(driver,tag=""):
     # Search by ID: zli__CLV-main__ and check if class ZmRowDoubleHeader contains 'Unread'
    all_rows = driver.find_elements(By.CSS_SELECTOR, '[id^="zli__CLV-main__"]')

    for row in all_rows:
        if 'Unread' in row.find_element(By.CLASS_NAME, 'ZmRowDoubleHeader').get_attribute('class'):
            # Scroll down to load more emails
            driver.find_element(By.TAG_NAME, 'body').send_keys(Keys.PAGE_DOWN)
            # Click on mail with stats unread
            row.click()
            time.sleep(5)
            # Click on first hyperlink
            if tag in ("hyperlink"):
                click_specific_hyperlink_in_email(driver)
                return
            # Click on first file download
            if tag in ("download"):
                #############################
                attachment_div = WebDriverWait(driver, 5).until(
                    EC.presence_of_element_located((By.XPATH, '//div[contains(@id,"zv__CLV__main_MSGC")]'))
                )
                print(f'{attachment_div}')
                dynamic_id_part = attachment_div.get_attribute('id').split('zv__CLV__main_MSGC')[-1].split('_attLinks')[0] 
                # check_id = attachment_div.get_attribute('id')
                # print(attachment_div.find_element(By.XPATH, f'.//a[contains(@id, "main_MSGC{dynamic_id_part}_downloadAll")]'))  
                print(f"Dynamic ID part: {dynamic_id_part}")              
                # get all attachment in message
                attachLink = driver.find_elements(By.CSS_SELECTOR, 'a.AttLink')
                # find message have button download all
                for index in attachLink:
                    if f'main_MSGC{dynamic_id_part}_downloadAll' in index.get_attribute('id'):
                        click_any_attachment_download(driver,download_option="all", index_values=[])
                # if can't file button download all, just download first attachment in message
                click_any_attachment_download(driver,download_option="index", index_values=[2])
                return
            return
                
            time.sleep(5)

    print("No unread email found")



def open_all_email_unread(driver):
     # Search by ID: zli__CLV-main__ and check if class ZmRowDoubleHeader contains 'Unread'
    all_rows = driver.find_elements(By.CSS_SELECTOR, '[id^="zli__CLV-main__"]')

    for row in all_rows:
        if 'Unread' in row.find_element(By.CLASS_NAME, 'ZmRowDoubleHeader').get_attribute('class'):
            # Scroll down to load more emails
            driver.find_element(By.TAG_NAME, 'body').send_keys(Keys.PAGE_DOWN)
            # Click on mail with stats unread
            row.click()
            time.sleep(5)

    print("No unread email found")

def open_email__new_click_hyperlink_in_email(driver, method="index", value=[]):
    # Search by ID: zli__CLV-main__ and check if class ZmRowDoubleHeader contains 'Unread'
    all_rows = driver.find_elements(By.CSS_SELECTOR, '[id^="zli__CLV-main__"]')

    for row in all_rows:
        if 'Unread' in row.find_element(By.CLASS_NAME, 'ZmRowDoubleHeader').get_attribute('class'):
            row.click()
            click_specific_hyperlink_in_email(driver, method, value)
            return
    print("No unread email found")


def open_email_click_download_in_email(driver, download_option="all", index_values=[]):
    all_rows = driver.find_elements(By.CSS_SELECTOR, '[id^="zli__CLV-main__"]')

    for row in all_rows:
        if 'Unread' in row.find_element(By.CLASS_NAME, 'ZmRowDoubleHeader').get_attribute('class'):
            row.click()
            click_any_attachment_download(driver, download_option, index_values)
            time.sleep(10)
            return
    print("No unread email found")

