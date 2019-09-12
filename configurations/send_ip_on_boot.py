#!/usr/bin/python3

import socket
import smtplib
import os
import sys
import credentials

# secret information
sender_address = credentials.gmail_address
sender_password = credentials.gmail_password
sender_server = "smtp.gmail.com"
sender_port = 587
recipient_address = credentials.gmail_address


def get_device_ip_address():
    hostname = socket.gethostname()
    IPAddr = socket.gethostbyname(hostname)
    return f"Hostname: {hostname}, IP: {IPAddr}"


def send_email(text):
    try:
        message = (
            "From: "
            + sender_address
            + "\nTo: "
            + recipient_address
            + "\nSubject: Device Information\n\n"
            + text
        )

        server = smtplib.SMTP(sender_server, sender_port)
        server.ehlo()
        server.starttls()
        server.login(sender_address, sender_password)
        server.sendmail(sender_address, recipient_address, message)
        server.close()
        print("Message sent:\n", message)

    except:
        print("failed to send email")


message = get_device_ip_address()
print(message)
print("Sending email, can take a while.")
send_email(message)
print("Done.")

sys.exit()
