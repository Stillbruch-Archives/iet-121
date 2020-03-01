 #define LED_1 13
 #define LED_2 12 
 #define LED_3 11
 #define LED_4 10 
 #define Led1On  digitalWrite (LED_1,LOW)   
 #define Led1Off digitalWrite (LED_1,HIGH)  
 #define Led2On  digitalWrite (LED_2,LOW)  
 #define Led2Off digitalWrite (LED_2,HIGH)   
 #define Led3On  digitalWrite (LED_3,LOW)  
 #define Led3Off digitalWrite (LED_3,HIGH)  
 #define Led4On  digitalWrite (LED_4,LOW)
 #define Led4Off digitalWrite (LED_4,HIGH)
 #define P1 A1 
 #define P2 A2               
 #define P3 A3
 #define P1On  (digitalRead(P1) == 0)
 #define P1Off (digitalRead(P1) == 1) 
 #define P2On  (digitalRead(P2) == 0)
 #define P2Off (digitalRead(P2) == 1)
 #define P3On  (digitalRead(P3) == 0)
 #define P3Off (digitalRead(P3) == 1) 
 #define SPKR 3
 #define SpkrOn  digitalWrite (SPKR, LOW)
 #define SpkrOff digitalWrite (SPKR, HIGH)