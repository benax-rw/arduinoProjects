String  str = "A1N c2 t120 d4 t0 b5 t0 a2 t368 e2 t452 1c t0 e1 t600";
String strs[20];
int StringCount = 0;

void setup (void)
{
  Serial.begin (115200);
  delay(200);
  
  Serial.println(str);

  // Split the string into substrings
  while (str.length() > 0)
  {
    int index = str.indexOf(' ');
    if (index == -1) // No space found
    {
      strs[StringCount++] = str;
      break;
    }
    else
    {
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
  }

  // Show the resulting substrings
  for (int i = 0; i < StringCount; i++)
  {
    Serial.print(i);
    Serial.print(": \"");
    Serial.print(strs[i]);
    Serial.println("\"");
  }
}

void loop () {}
