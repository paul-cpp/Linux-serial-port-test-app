Тестировалось на паре вирутальных портов.
Для создания пары последовательных портов нужно выполнить команду:
socat PTY,link=/dev/ttyS10 PTY,link=/dev/ttyS11
Также нужно добавить пользователя в группу dialout:
sudo usermod -a -G dialout <user>
Если порты все еще не удается открыть, то в другом терминале выполнить:
sudo chmod 666 /dev/ttyS10
sudo chmod 666 /dev/ttyS11

Файл, который необходимо передать на сервер, находится в корневом каталоге


