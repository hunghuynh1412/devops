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

def send_email( driver, toEmail, subject, content, filePath):
    #windows define with 2 '\'
    body_text = content.split('\\n')
    attachment_path = os.path.join(filePath)

    # Click on New Message button
    new_msg_btn = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, 'zb__NEW_MENU')))
    new_msg_btn.click()
    
    # Fill in the "To" field
    to_field = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, 'zv__COMPOSE-1_to_control')))
    to_field.send_keys(toEmail)
    
    # Fill in the "Subject" field
    subject_field = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, 'zv__COMPOSE-1_subject_control')))
    subject_field.send_keys(subject)
    
    # Switch to the email content iframe
    driver.switch_to.frame(WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, 'ZmHtmlEditor1_body_ifr'))))
    
    # Find the body of the email
    body = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, 'tinymce')))
    
    # Enter email content
    for index_content in body_text:
        body.send_keys(index_content)
        body.send_keys(Keys.ENTER)
    
    # Switch back to default content
    driver.switch_to.default_content()
    if filePath != "":
        # Attach file
        attach_button = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, "zb__COMPOSE-1___attachments_btn"))
        )
        attach_button.click()
        time.sleep(2)  # wait for the Open dialog to appear

        # Use pyautogui to input the file path
        pyautogui.typewrite(attachment_path)
        pyautogui.press("enter")

    # Click the Send button
    time.sleep(5)
    send_btn = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, 'zb__COMPOSE-1__SEND')))
    send_btn.click()