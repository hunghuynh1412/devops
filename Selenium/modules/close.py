
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



def logout(driver):
    try:
        # Locate and click the dropdown button
        dropdown_button = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, 'DWT29'))
        )
        dropdown_button.click()
        time.sleep(5)

        # Locate and click the Sign Out button
        logout_button = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, 'logOff'))
        )
        logout_button.click()

    except Exception as e:
        print(f"An error occurred: {e}")

def close_program(driver):
    driver.quit()