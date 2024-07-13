// mfrc522 functions
bool card_id_match() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // show card UID
    Serial.print(F("Card UID:"));
    print_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));  // card type

    // contrast UID
    bool they_match1 = true, they_match2 = true, they_match3 = true, they_match4 = true;
    for (int j = 0; j < 4; j++) {  // len(uid) = 4
      if (uid1[j] != mfrc522.uid.uidByte[j]) {
        they_match1 = false;
        break;
      }
    }
    for (int j = 0; j < 4; j++) {
      if (uid2[j] != mfrc522.uid.uidByte[j]) {
        they_match2 = false;
        break;
      }
    }
    for (int j = 0; j < 4; j++) {
      if (uid3[j] != mfrc522.uid.uidByte[j]) {
        they_match3 = false;
        break;
      }
    }
    for (int j = 0; j < 4; j++) {
      if (uid4[j] != mfrc522.uid.uidByte[j]) {
        they_match4 = false;
        break;
      }
    }

    bool contrast_result = they_match1 || they_match2 || they_match3 || they_match4;
    if (contrast_result) {
      Serial.print(F("Access Granted!\n"));
    } else {
      Serial.print(F("Access Denied!\n"));
    }
    mfrc522.PICC_HaltA();
    return contrast_result;
  }
}

void print_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}