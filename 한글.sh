//리눅스 한글
//스크립트 작성
/*
vscode에서 한영전환 안될때

$ sudo snap remove code(이미 설치된 snap 형식 제거)
sudo dpkg -i code_1.58.2-1626302803_amd64.deb
만약 설치중에 의존 라이브러리 없다고 나오면  sudo apt -f install
*/
//ibus-setup -> 입력기(input method)에서 한글 추가
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


참고 사이트 : https://omnil.tistory.com/155
*/
