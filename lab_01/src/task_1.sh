#!/bin/bash
BASE_DIR="/home/vestfal/itmo/lab1"
FOLDER_MAX="$BASE_DIR/folder_max"
FOLDER_MIN="$BASE_DIR/folder_min"

#1
echo "2.1 Создание директории..."
mkdir -p "$FOLDER_MAX"
mkdir -p "$FOLDER_MIN"

#2
echo "2.2 Создание групп..."
sudo groupadd group_max 
sudo groupadd group_min

#3
echo "2.3 Создание пользователей..."
sudo useradd -m -G group_max user_max_1
sudo useradd -m -G group_min user_min_1

#4 
echo "2.4 Настройка прав доступа..."
sudo chown -R :group_max "$FOLDER_MAX"
sudo chown -R :group_min "$FOLDER_MIN"

sudo chmod 770 "$FOLDER_MAX"
sudo chmod 770 "$FOLDER_MIN"

sudo usermod -a -G group_min user_max_1

#5 
echo "2.5 Создание и исполнение скрипта в директории folder_max, который пишет текущую дату/время в файл output.log."
cat > "$FOLDER_MAX/write_data.sh" << 'EOF'
#!/bin/bash
# Скрипт для записи текущей даты и времени в файл output.log
date >> "$(pwd)/output.log"
echo "Дата и время записаны в output.log"
EOF

# Делаем скрипт исполняемым
chmod +x "$FOLDER_MAX/write_date.sh"

# Исполняем скрипт
"$FOLDER_MAX/write_date.sh"

#teardown 
sudo rm -r /home/vestfal/itmo/lab1

sudo deluser --remove-home user_max_1
sudo deluser --remove-home user_min_1

sudo groupdel group_max 
sudo groupdel group_min 