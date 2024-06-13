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


def reply_email(driver, content):
    body_text = content

    try:
        print("Waiting for email footer to be available...")
        
        # Using XPath with contains function to find the dynamic ID
        email_footer = WebDriverWait(driver, 5).until(
            EC.presence_of_element_located((By.XPATH, '//div[contains(@id,"main_MSGC") and @class="footer"]'))
        )
        
        print("Waiting for reply button to be available...")
        
        # Wait for an additional 1 second for the reply button to be rendered
        time.sleep(1)
        
        # Find the reply button within the footer div and click it
        reply_button = email_footer.find_element(By.XPATH, './/a[contains(@id,"__footer_reply")]')
        
        print("Clicking reply button...")
        reply_button.click()
        
        print("Waiting for textarea to be available...")
        
        reply_textarea = WebDriverWait(driver, 5).until(
            EC.presence_of_element_located((By.XPATH, '//textarea[contains(@id,"reply_replyInput") and @class="ReplyTextarea"]'))
        )
        
        print("Entering text into textarea...")
        
        reply_textarea.send_keys(body_text)
        
        print("Waiting for Send button to be available...")
        
        send_button = WebDriverWait(driver, 5).until(
            EC.presence_of_element_located((By.XPATH, '//td[contains(@id,"Rep__SEND_title") and @class="ZWidgetTitle"]'))
        )
        
        print("Clicking Send button...")
        
        send_button.click()

        # Wait 10 seconds to allow any subsequent actions to occur (like opening the reply email editor)
        time.sleep(10)
        
    except TimeoutException as ex:
        print("Could not find the email footer or reply button. Exception:", ex)

def open_email__new_reply_email(driver, content):
     # Search by ID: zli__CLV-main__ and check if class ZmRowDoubleHeader contains 'Unread'
    all_rows = driver.find_elements(By.CSS_SELECTOR, '[id^="zli__CLV-main__"]')

    for row in all_rows:
        if 'Unread' in row.find_element(By.CLASS_NAME, 'ZmRowDoubleHeader').get_attribute('class'):
            row.click()
            reply_email(driver, content)
            return
    print("No unread email found")