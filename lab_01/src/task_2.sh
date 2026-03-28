echo "2.1. Создание скрипта write_date.sh"

cat > write_date.sh << EOF
#!/bin/bash
CURRENT_DIR="\$(pwd)"
date >> "\$CURRENT_DIR/output.log"
echo "Текущая дата и время записаны в \$CURRENT_DIR/output.log"
EOF

chmod +x write_date.sh
echo "Скрипт write_date.sh создан"

echo "----------------------------------------"
echo "2.2. Создание Dockerfile"

cat > Dockerfile << 'EOF'
FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    nano \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY write_date.sh /app/write_date.sh
RUN chmod +x /app/write_date.sh

RUN useradd -m -s /bin/bash docker_user && \
    echo "docker_user:docker_pass" | chpasswd

WORKDIR /home/docker_user
CMD ["/bin/bash"]
EOF

echo "Dockerfile создан"

echo "----------------------------------------"
echo "2.3. Сборка образа (docker build)"

sudo docker build -t lab1:latest .
echo "Образ lab1:latest собран"

echo "----------------------------------------"
echo "2.4. Запуск образа и выполнение скрипта"

sudo docker run -it --rm lab1:latest bash -c '
	echo "Текущая директория"
	pwd
	echo "----------------------------------------"
	echo "Запуск скрипта write_data.sh"
	/app/write_date.sh
	echo "----------------------------------------"
	echo "Содержимое output.log"
	cat /home/docker_user/output.log
	echo "----------------------------------------"	
	echo "Список пользователей в системе"
	cat /etc/passwd  
'

