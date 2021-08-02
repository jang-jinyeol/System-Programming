//리눅스 한글
//스크립트 작성
#!/bin/bash
setkeycodes 72 122
setkeycodes 71 123

/*
스크립트 실행
chmod +x hangul.sh
sudo ./hangul.sh

cd /etc/systemd/system/
sudo vi hangul.service

아래 내용 작성
[Unit]
Description=Change Hangul keycode
 
[Service]
ExecStart=/스크립트가 설정된 경로/hangul.sh
 
[Install]
WantedBy=multi-user.target

------------------

$ sudo systemctl enable hangul

$ sudo systemctl start hangul

sudo systemctl status hangul(작동확인)

재부팅
*/
