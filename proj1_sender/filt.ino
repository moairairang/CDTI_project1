void filt(){
float flexValue1 = analogRead(flexPin1);
  float flexValue2 = analogRead(flexPin2);
  float flexValue3 = analogRead(flexPin3);
  float flexValue4 = analogRead(flexPin4);

  flexFilt1 = 0.854 * flexFilt1 + 0.0728 * flexValue1 + 0.0728 * flexPrev1;
  flexPrev1 = flexValue1;

  flexFilt2 = 0.854 * flexFilt2 + 0.0728 * flexValue2 + 0.0728 * flexPrev2;
  flexPrev2 = flexValue2;

  flexFilt3 = 0.854 * flexFilt3 + 0.0728 * flexValue3 + 0.0728 * flexPrev3;
  flexPrev3 = flexValue3;

  flexFilt4 = 0.854 * flexFilt4 + 0.0728 * flexValue4 + 0.0728 * flexPrev4;
  flexPrev4 = flexValue4;
}