import smtplib
import json
import os
# from email.message import EmailMessage
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart

# Define the EmailSender class
class EmailSender:
    # Initialize the class with configurations from a JSON file
    def __init__(self, config_file):
        with open(config_file, 'r') as f:
            config = json.load(f)
        self.smtp_server = config.get("smtp_server")
        self.smtp_port = config.get("smtp_port")
        self.smtp_user = config.get("smtp_user")
        self.smtp_pass = config.get("smtp_pass")
        self.email_subject = config.get("email_subject")
        self.email_content = config.get("email_content")
        self.attachments = config.get("attachments", [])
        self.hyperlink = config.get("hyperlink", {})

    # Function to send email
    def send_email(self, recipient):
        # Create a multipart email message
        msg = MIMEMultipart("alternative")
        msg["Subject"] = self.email_subject
        msg["From"] = self.smtp_user
        msg["To"] = recipient

        # Attach the email content
        text_content = self.email_content

        # Add hyperlink if available
        if self.hyperlink:
            text_content += f'<br>With embedded hyperlink: <a href="{self.hyperlink["url"]}">{self.hyperlink["text"]}</a><br>'
        
         # Finalize the email content
        text_content += "Thank you."
        text_msg = MIMEApplication(text_content, "html")
        msg.attach(text_msg)

        # Attach files if available
        for file_path in self.attachments:
            if os.path.exists(file_path):
                with open(file_path, "rb") as f:
                    part = MIMEApplication(f.read(), Name=os.path.basename(file_path))
                    part['Content-Disposition'] = f'attachment; filename="{os.path.basename(file_path)}"'
                    msg.attach(part)

        # Send the email
        try:
            with smtplib.SMTP(self.smtp_server, self.smtp_port) as server:
                print("Starting TLS...")
                server.starttls()
                print(f"Logging in as {self.smtp_user}...")
                server.login(self.smtp_user, self.smtp_pass)
                print(f"Sending email to {recipient}...")
                server.send_message(msg)
                print("Email sent successfully.")
        except Exception as e:
            print(f"Failed to send email: {e}")

# Entry point of the program
if __name__ == "__main__":
    # Specify the path to the JSON configuration file
    # config_file = "config_send_mail_python_normal.json" # For Normal Text Email
    # config_file = "config_send_mail_python_hyperlink.json" # For Text Email with Hyperlink
    config_file = "config_send_mail_python_hyperlink_attachment.json" # For Text Email with Hyperlink and Attachment
    # config_file = "config_send_mail_python_attachment.json" # For Normal Text Email with Attachment
    
    # Initialize the EmailSender class and send the email
    sender = EmailSender(config_file)
    sender.send_email("admin@ubuntu.local")
