import pywhatkit as kit
import sys
import time

def format_phone_number(phone_number):
    if not phone_number.startswith('+') or len(phone_number) != 13:
        return None
    return phone_number.replace(' ', '')


def send_whatsapp_message(name, phone_number):
    try:
        formatted_number = format_phone_number(phone_number)
        if not formatted_number:
            raise ValueError("Country Code Missing in Phone Number!")

        print(f"Sending message to: {formatted_number}")
        message = f"Hello {name}! 🎂\n🎉🎈 I hope the coming year brings you health, happiness, and success. May all your wishes come true! 🎊\nHappy Birthday! 🌟"
        
        current_time = time.localtime()
        print(f"Current time: {current_time.tm_hour}:{current_time.tm_min}")
        print("Opening WhatsApp Web to send message...")


        kit.sendwhatmsg(formatted_number, message, current_time.tm_hour, current_time.tm_min + 1)
        print(f"Message sent to {name} at {formatted_number}.")
    except Exception as e:
        print(f"Failed to send message to {name}. Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) == 3:
        send_whatsapp_message(sys.argv[1], sys.argv[2])
    else:
        print("Usage: python send_whatsapp.py [name] [phone_number]")
