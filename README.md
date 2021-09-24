#  QT Treiber für BLE uart service

 Für unsere BLE (Bluetooth low energy) basierten EMG und IMU Sensoren möchten wir gerne basierend auf QT Treiber entwickeln, mit denen man die Daten auslesen und speichern kann. Hierfür müssen die folgenden Punkte bearbeitet werden: 

1. Bestehende C++ Klasse muss angepasst werden für QT. 

2. Implementierung eines automatischen reconnects falls ein Sensor außer Reichweite ist und wieder in Reichweite kommt. 

3. Test der Treiber unter Linux Ubuntu 18.04 und Windows 10.

4. OPTIONAL: Device Firmware Update 

Alle Details werden über das Ticketsystem von gitlab erledigt. Die Dokumentation soll komplett in markdown erledigt werden.
