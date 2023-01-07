﻿# WINPS2VKBD

### ver1.0.0
- メニューを英語化し、View項目を追加した
- bugfix キー押しっぱなしの後にキーを離すと押されたままになることをがある
キーボードのキー押下を検知するには、WM_KEYDOWN、WM_SYSKEYDOWN メッセージを受け取ることで判断しているが、キー開放を検知するときに、WM_KEYUP、WM_SYSKEYYUPメッセージは使用していない。WH_KEYBOARD_LLメッセージをフックプロシージャを用いて受信してキー開放を判断している。キーを押下しその後のキー開放の前に、何らかの理由でキーボードフォーカスが外れてしまうとWM_KEYUP、WM_SYSKEYYUPメッセージを受信できなくなり、キーが押されっぱなしと判断されてしまうことがあるので、この方法としている。この不具合は、キーを長く押しているとキーリピート機能でWM_KEYDOWNを繰り返し受信するが、WH_KEYBOARD_LLメッセージでキー開放を受信してもその後にキーリピート機能によるWM_KEYDOWNを受信してしまうことがあるために発生した。キーリピート機能によるWM_KEYDOWNとそうではないWM_KEYDOWNとは受信時のflag値で判断できるので、その判断を行うようにし、この不具合は解決した。
- bugfix CAPS LOCKなどのLEDが正しく転倒しないことがある
- COM Port listの文字を大きくし、またダブルクリックで選択できるようにして使いやすくした
- capsとかなキーの近くにインジケーター表示を設けた
- bugfix PowerToysで位置を入れ替えたキーの押下を正しく判断できない

### ver0.9.3
- リファクタリング。

### ver0.9.2
- USBケーブルがPCから抜け、再度接続されたときにCOMの状態が復元しなかった不具合を改善した

### ver0.9.1
- ver0.9.0 では対応していなかったMSX Keybord 上のボタン[PSG↑][PSG↓][FM↑][SCC↑][Slot1Conf][Slot2Conf]に対応しました。
- ウィンドウ内のキーをマウス押下しながらウィンドウ外へ移動し、マウスボタンを解放すると、キーが押しっぱなしになる不具合を修正した。マウスキャプチャの方法を間違えていたのが原因でした
- ウィンドウ内のキーを押下中に補完おアプリケーションにフォーカスを奪われたら、押下していたキーを強制的に解放するようにしました

### ver0.9.0
- 初リリース