import serial
import wave
import time

# serial config
SERIAL_PORT = "COM12"
BAUD_RATE = 921600
OUTPUT_FILENAME = "output_audio.wav"

# audio config
SAMPLE_RATE = 41100  
CHANNELS = 1          # Mono
SAMPLE_WIDTH = 2      # 4 bytes = 32-bit audio
RECORD_SECONDS = 10   

def record_audio_from_serial():
    audio_data = []     # will hold samples
    
    try:
        connection = serial.Serial(
            port= SERIAL_PORT,
            baudrate=BAUD_RATE,
            timeout=1
        )
        print(f"Connction to {SERIAL_PORT} was successful")

        time.sleep(2)   # wait for everything to be initialized
        print(f"Recording audio for {RECORD_SECONDS} seconds")
        start_time = time.time()

        while (time.time() - start_time) < RECORD_SECONDS:
            data = connection.read(connection.in_waiting)   # read data in the input buffer
            if data:
                audio_data.append(data)     # add the data to the array

        connection.close()
        print("Recording stopped")
    
    except serial.SerialException as e:
        print(f"Failed to establish connection. {e}")

    if not audio_data:
        print("No audio data available")
    
    pcm_data = b"".join(audio_data)
    print(f"Received {len(audio_data)} bytes")

    try:
        with wave.open(OUTPUT_FILENAME, 'wb') as wav_file:
            wav_file.setnchannels(CHANNELS)
            wav_file.setsampwidth(SAMPLE_WIDTH)
            wav_file.setframerate(SAMPLE_RATE)
            wav_file.writeframes(pcm_data)
        print(f"Audio saved successfully to {OUTPUT_FILENAME}")
    except Exception as e:
        print(f"Error writing WAV file: {e}")

if __name__ == '__main__':
    record_audio_from_serial()