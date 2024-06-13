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




def init_driver():
    chrome_options = webdriver.ChromeOptions()
    chrome_options.add_argument("--disable-notifications")  # Disable notifications
    chrome_options.add_argument("--disable-popup-blocking")  # Disable popup blocking
    chrome_options.add_argument("--disable-infobars")
    chrome_options.add_argument("--disable-extensions")
    chrome_options.add_argument("--start-maximized")  # Start browser maximized
    chrome_options.add_argument("--disable-web-security")  # Disable web security to handle CORS
    chrome_options.add_argument("--no-default-browser-check")  # Disable default browser check
    prefs = {'profile.default_content_setting_values.notifications': 2}
    chrome_options.add_experimental_option('prefs', prefs)
    chrome_options.accept_insecure_certs = True
    # driver = webdriver.Chrome(options=chrome_options)
    
    service = Service(executable_path='.\chromedriver.exe')
    driver = webdriver.Chrome(service=service,options=chrome_options)
    # driver = webdriver.Chrome(executable_path="../chromedriver.exe")
    return driver


def login(driver, domain, username, pasword):
    driver.get(domain)
    try:
        print("Waiting for username field...")
        field_username = WebDriverWait(driver, 20).until(EC.presence_of_element_located((By.ID, 'username')))
        
        print("Waiting for password field...")
        field_password = WebDriverWait(driver, 20).until(EC.presence_of_element_located((By.ID, 'password')))
        
        print("Sending keys to fields...")
        field_username.send_keys(username)
        field_password.send_keys(pasword)
        
        print("Finding and clicking Sign In button...")
        sign_in_button = WebDriverWait(driver, 20).until(EC.presence_of_element_located((By.CSS_SELECTOR, 'body > div > div.center > div.contentBox > form > table > tbody > tr:nth-child(3) > td.submitTD > input.ZLoginButton.DwtButton')))
        sign_in_button.click()
        
    except TimeoutException as ex:
        print("An exception occurred: ", ex.msg)