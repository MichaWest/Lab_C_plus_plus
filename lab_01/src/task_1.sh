#!/bin/bash
BASE_DIR="/home/vestfal/itmo/Lab_C_plua_plus/lab_01/src"
FOLDER_MAX="$BASE_DIR/folder_max"
FOLDER_MIN="$BASE_DIR/folder_min"

#1
echo "1.1 Создание директории..."
mkdir -p "$FOLDER_MAX"
mkdir -p "$FOLDER_MIN"

#2
echo "----------------------------------------"
echo "1.2 Создание групп..."
sudo groupadd group_max 
sudo groupadd group_min

#3
echo "----------------------------------------"
echo "1.3 Создание пользователей..."
sudo useradd -m -G group_max user_max_1
sudo useradd -m -G group_min user_min_1

#4 
echo "----------------------------------------"
echo "1.4 Настройка прав доступа..."
sudo chown -R :group_max "$FOLDER_MAX"
sudo chown -R :group_min "$FOLDER_MIN"

sudo chmod 770 "$FOLDER_MAX"
sudo chmod 770 "$FOLDER_MIN"

sudo usermod -a -G group_min user_max_1

#5 
echo "----------------------------------------"
echo "1.5 Создание и исполнение скрипта в директории folder_max, который пишет текущую дату/время в файл output.log."
cat > "$FOLDER_MAX/write_data.sh" << EOF
#!/bin/bash
# Скрипт для записи текущей даты и времени в файл output.log
date >> "$FOLDER_MAX/output.log"
echo "Дата и время записаны в $FOLDER_MAX/output.log"
EOF

echo "Делаем скрипт исполняемым"
chmod +x "$FOLDER_MAX/write_data.sh"

echo "Исполняем скрипт от пользователя user_max_1"
sudo -u user_max_1 "$FOLDER_MAX/write_data.sh"

echo "Содержимое файла output.log"
cat "$FOLDER_MAX/output.log"

#6 
echo "----------------------------------------"
echo "1.6 Создание и исполнение скрипта в директории folder_max (пользователем user_max_1), который пишет дату/время в output.log в директории folder_min."

cat > "$FOLDER_MAX/write_to_min.sh" << EOF
#!/bin/bash
# Записываем текущую дату и время в файл output.log в директории folder_min
date >> "$FOLDER_MIN/output.log"
echo "Дата и время записаны в $FOLDER_MIN/output.log"
EOF

echo "Делаем скрипт исполняемым"
chmod +x "$FOLDER_MAX/write_to_min.sh"

echo "Исполняем скрипт от пользователя user_max_1"
sudo -u user_max_1 "$FOLDER_MAX/write_to_min.sh"

echo "Содержимое файла output.log"
cat "$FOLDER_MIN/output.log"

#7 
echo "----------------------------------------"
echo "1.7 Исполнение скрипта в директории folder_max (пользователем user_min_1), который пишет дату/время в output.log в директории folder_min."

echo "Исполняем скрипт от пользователя user_min_1"
sudo -u user_min_1 "$FOLDER_MAX/write_to_min.sh"

#8
echo "----------------------------------------"
echo "1.8 Исполнение скрипта в директории folder_min (пользователем user_min_1), который пишет дату/время в output.log в директории folder_max."

echo "Исполняем скрипт от пользователя user_min_1"
sudo -u user_min_1 "$FOLDER_MAX/write_data.sh"

#9
echo "----------------------------------------"
echo "1.9 Выводим перечень прав доступа у папок *_min/ *_max, а также у всего
содержимого внутри"

echo "=== Права доступа для $FOLDER_MAX ==="
ls -ld "$FOLDER_MAX"
echo "Содержимое $FOLDER_MAX:"
ls -la "$FOLDER_MAX"

echo -e "\n=== Права доступа для $FOLDER_MIN ==="
ls -ld "$FOLDER_MIN"
echo "Содержимое $FOLDER_MIN:"
ls -la "$FOLDER_MIN"

#teardown 
echo "----------------------------------------"
echo "teardown"
sudo rm -r /home/vestfal/itmo/lab1

sudo deluser --remove-home user_max_1
sudo deluser --remove-home user_min_1

sudo groupdel group_max 
sudo groupdel group_min 
