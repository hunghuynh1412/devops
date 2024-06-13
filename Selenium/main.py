# import time 
# import pyautogui
# import os
# import json
# from selenium.webdriver.chrome.service import Service
# from selenium import webdriver
# from selenium.webdriver.chrome.options import Options
# from selenium.webdriver.common.keys import Keys
# from selenium.webdriver.common.by import By
# from selenium.webdriver.common.alert import Alert
# from selenium.webdriver.support.ui import WebDriverWait
# from selenium.webdriver.support import expected_conditions as EC
# from selenium.common.exceptions import TimeoutException
from modules.send_email import *
from modules.init_information import *
from modules.open_email import *
from modules.reply_email import *
from modules.Utils import *
from modules.close import *
import getopt, sys

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

def main ():
    # Remove 1st argument from the
    # list of command line arguments
    argumentList = sys.argv[1:]
    # index of element Content
    index = 0
    # if contain Content in argumentList then get index element of Content
    if "--Content" in argumentList:
        index = argumentList.index("--Content")
        
    #length of array argumentList
    length = len(argumentList)
    # if length of argumentList equal to index that mean the Content doesn't have value, so need to add the value init for Content
    if length - 1 == index:
         argumentList.append("")
    # Options
    options = "ha:u:p:s:f:m:"
    
    # Long options
    # Content can set to be NULL for bypass requires argument
    long_options = ["Help", "Action=", "Username=", "Password=", "Server=", "File=", "toEmail=", "Subject=", "Content=","Mode=","Tag="]
    #init data
    filePath = ""
    toEmail = "UserDefault@mail.local"
    subject = "<No Subject>"
    content = ""
    mode = "default"
    tag = ""
    try:
        # Parsing argument
        arguments, values = getopt.getopt(argumentList, options, long_options)
        
        # checking each argument
        for currentArgument, currentValue in arguments:
    
            if currentArgument in ("-h", "--Help"):
                print ("Displaying Help")
                print ("Displaying Help")
                print ("Displaying Help")
                print ("Displaying Help")
                print ("Displaying Help")
                
            elif currentArgument in ("-a", "--Action"):
                #param required
                action = currentValue
            elif currentArgument in ("-u", "--Username"):
                #param required
                userName = currentValue
            elif currentArgument in ("-p", "--Password"):
                #param required
                passWord = currentValue
            elif currentArgument in ("-s", "--Server"):
                #param required
                Server = currentValue
            elif currentArgument in ("--toEmail"):
                toEmail = currentValue
            elif currentArgument in ("--Subject"):
                subject = currentValue
            elif currentArgument in ("--Content"):
                content = currentValue
            elif currentArgument in ("-f", "--File"):
                filePath = currentValue
            elif currentArgument in ("-m", "--Mode"):
                mode = currentValue
            elif currentArgument in ("--Tag"):
                tag = currentValue
        close = True

        #init driver chrome before running
        driver = init_driver()
        #login in zimbra on chrome
        login(driver, Server, userName, passWord)

        time.sleep(5)
        if action in ("Send"):
            #action send email 
            send_email(driver, toEmail, subject, content, filePath)
        elif action in ("Reply"):
            open_email__new_reply_email(driver, content)
        elif action in ("Open"):
            if mode in ("subject"):
                if tag in ("hyperlink","download"):
                    open_email_by_subject(driver,subject,tag)
                else:
                    open_email_by_subject(driver,subject)
            elif mode in ("all"):
                open_all_email_unread(driver)
            else:
                if tag in ("hyperlink","download"):
                    open_newest_email(driver, tag)
                else:
                    open_newest_email(driver)

        time.sleep(5)

        #close action
        if close:
            logout(driver)
            time.sleep(5)
            close_program(driver)



    except getopt.error as err:
        # output error, and return with an error code
        print (str(err))

main()
    



# def main():
    

 # Perform actions
    # perform_action(open_email)

    # perform_action(open_email_new)

    # perform_action(open_email__new_click_hyperlink_in_email, method="index", value=0)
    # perform_action(open_email__new_click_hyperlink_in_email, method="attribute", value="https://vnexpress.net/")
    # perform_action(open_email__new_click_hyperlink_in_email, method="text", value="ngoisao.net")

    # perform_action(open_email_click_download_in_email, download_option="index", index_values=2)
    # perform_action(open_email_click_download_in_email, download_option="index", index_values=[2,3])
    # perform_action(open_email_click_download_in_email, download_option="all")

    # config = open_config_file('config_send_email.json')
    # perform_action(send_email, True, config)

    # config = open_config_file('config_reply_email.json')
    # perform_action(open_email__new_reply_email, True, config)

    # perform_action(find_and_process_new_email, close=False, download_option="index", index_values=[2])
    # perform_action(find_and_process_new_email, close=False, download_option="index", index_values=[2,3])
    # perform_action(find_and_process_new_email, close=False, download_option="all")
# main()