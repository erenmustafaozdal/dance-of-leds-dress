/* Arduino Lilypad ile harekete bağlı elbise üzerindeki ledleri yakma projesi 

MALZEMELER
- Arduino Lilypad Atmega32U4 Geliştirme Kartı
- LilyPad RGB - Üç Renk - LED (istenilen sayıda)
- LilyPad İvmeölçer- ADXL335

Yazar: Eren Mustafa Özdal [eren.060737@gmail.com] 
Tarih: 19/04/24
Lisans: (MIT Lisansı) - Bu kodu kullanmaktan ve bakımını yapmaktan çekinmeyin.
Eğer duygularınızı içtenlikle ifade ederseniz minnettar olurum.
*/

#include <math.h>  // Karekök fonksiyonu için

const int xpin = 2;  // İvmeölçerin X ekseni Arduino üzerindeki anolog pin 2'dir
const int ypin = 3;  // İvmeölçerin Y ekseni Arduino üzerindeki anolog pin 3'tür
const int zpin = 3;  // İvmeölçerin Z ekseni Arduino üzerindeki anolog pin 4'tür

// Parıltıları ayarlamak için bu sayı ile oynayın
// daha düşük sayı = daha hassas
#define MOVE_THRESHOLD 45

/*
X, Y, Z eksen değerlerini alır ve üç eksenli vektör büyüklüğünü hesaplayıp döndürür
Kaynak: http://en.wikipedia.org/wiki/Euclidean_vector#Length
*/
double calculateVector(int xpin, int ypin, int zpin) {
  /* Yeni bir sensör olayı alın */
  int x = analogRead(xpin);
  int y = analogRead(ypin);
  int z = analogRead(zpin);

  Serial.print("Accel X: " + String(x) + " ");
  Serial.print("Accel Y: " + String(y) + " ");
  Serial.print("Accel Z: " + String(z) + " ");

  double vectorLength = pow(x, 2) + pow(y, 2) + pow(z, 2);
  vectorLength = sqrt(vectorLength);
  Serial.println("Vektör Uzunluğu: " + String(vectorLength));

  return vectorLength;
}

void setup() {
  pinMode(xpin, INPUT);  // `xpin` ile belirlenen analog pin X ekseni için giriş olarak ayarlanır.
  pinMode(ypin, INPUT);  // `ypin` ile belirlenen analog pin Y ekseni için giriş olarak ayarlanır.
  pinMode(zpin, INPUT);  // `zpin` ile belirlenen analog pin Z ekseni için giriş olarak ayarlanır.

  Serial.begin(9600);  // 9600 seri port (boud rate) ile Arduino’nun haberleşmesi başlatılıyor
}

void loop() {

  // vektör uzunluğunu al
  double storedVector = calculateVector(xpin, ypin, zpin);

  // Biraz bekleyelim
  delay(100);

  // yeni vektör uzunluğunu al
  double newVector = calculateVector(xpin, ypin, zpin);

  // HAREKET EDİLMİŞ Mİ?
  // `newVector` ve `storedVector` değişkenleri arasındaki farkın, 
  // MOVE_THRESHOLD adlı sabitten büyük olup olmadığını kontrol edelim
  // İki vektör arasındaki fark hesaplanır
  double diff = abs(newVector - storedVector);
  Serial.println("FARK: " + String(diff));
  if (diff > MOVE_THRESHOLD) {
    Serial.println("Hareket edildi!");
  }
}
