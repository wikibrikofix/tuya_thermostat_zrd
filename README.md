# Tuya Thermostat for Floor Heating Zigbee with custom firmware

**Tuya Thermostat model**

	"_TZE204_u9bfwha0"
	"_TZE204_aoclfnxz"
	"_TZE204_edl8pz1k"

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/TYBAC-006.png"/>

**Автор не несет никакой отвественности, если вы, воспользовавшись этим проектом, превратите свой умный термостат в полоумный.**

Проверялись только термостаты перечисленные выше. Если у вас другая сигнатура, лучше не заливать, не проверив на совпадение датапоинтов.

Проверялся только в zigbee2mqtt.

## Зачем. 

Чтобы не спамил в сеть. Первый экземпляр (см. выше) посылал 25 пакетов каждые 8 секунд.

## Что получилось. 

**About**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_about.jpg"/>

**Exposes**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_exposes.jpg"/>

**Reporting**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_reporting.jpg"/>


## Как обновить.

Сначала подключаем к z2m два внешних [конвертора](https://github.com/slacky1965/tuya_thermostat_zrd/tree/main/zigbee2mqtt/convertors) `tuya_thermostat_orig.js` и `tuya_thermostat.js`. Первый активирует OTA в z2m для термостата с прошивкой от Tuya. Второй - для термостата с кастомной прошивкой. В конверторах менять ничего не надо, все должно подхватиться автоматом.

Далее нужно добавить локальное хранилище обновлений. 

Создаем директорию в директории z2m `images` и кладем туда файл `1141-d3a3-1111114b-tuya_thermostat_zrd.zigbee`.

Создаем файл в директории z2m, например с именем `local_ota_index.json`. Добавляем в в него вот такую запись

```
	[
      {
        "url": "images/1141-d3a3-1111114b-tuya_thermostat_zrd.zigbee",
        "force": true
      }
	]
```
Далее добавляем это все в конфиг z2m (configuration.yaml). Должно получиться что-то в этом роде.

```
external_converters:
  - tuya_thermostat_orig.js
  - tuya_thermostat_model1.js
ota:
  zigbee_ota_override_index_location: local_ota_index.json
```

Далее перегружаем z2m. И видим у нас новое устройство (если термостат уже был в сети и виден в z2m).

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_1.jpg"/>

Далее идем в раздел OTA. И видим там свое устройство. Жмем проверить обновления.
	
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_1.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_2.jpg"/>

Жмем на красную кнопку. И обновляемся.

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_3.jpg"/>

Если все не так, как описано, значит вы что-то сделали не по инструкции (не положили файл куда нужно, не перегрузили z2m).

Далее ждем окончания. После этого мы в OTA видим наш термостат со старым именем, но уже с новыми `Firmware build date` и `Firmware version`.

Далее идем в радел `Devices` и жмем на нашем термостате "Корзинку", т.е. удаляем его из сети.

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_remove_1.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_remove_2.jpg"/>

И перегружаем z2m. Далее ждем, пока он загрузится и спариваем термостат по-новой - при выключенном устройстве, зажимаем стрелочку вниз до появления мигающего значка сети.

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_joined.jpg"/>

Все.

P.S. В реальной работе не проверялось, требует всестороннего тестирования.

Более развернутое описание для саомго первого термостата [тут](https://habr.com/ru/articles/864740)

Спасибы :))

- [@ruslikx3m](https://t.me/ruslikx3m) за первый предоставленный термостат _TZE204_u9bfwha0 на растерзание.

- [@immortal_serg](https://t.me/immortal_serg) за предоставленный термостат _TZE204_edl8pz1k.

- [https://github.com/doctor64](https://github.com/doctor64) [@doctor_64](https://t.me/doctor_64) - за желание всегда помочь и направить в правильное русло.

- [https://github.com/devbis](https://github.com/devbis) [@Belokobylskiy](https://t.me/Belokobylskiy) - за идеи и написание скриптов на Питоне.

- [@goofyk](https://t.me/goofyk) - за терпение и за хорошее знание z2m.

- [https://github.com/pvvx](https://github.com/pvvx) - за замечательный программматор для чипов Telink.

## История версий
- 1.0.01
	- Начало.
- 1.0.02
	- Релиз. Удален из-за проблемы с обновлением OTA.
- 1.0.03
	- Устранена проблема с возможностью установить температуру нагрева выше порога, заданного в maxHeatSetpoint. 
	- Откорректирован конвертор на предмет проброса термостата в Home Assistant. 
	- Добавлены функции callback удаленных команд в структуру DataPoint'ов. 
	- Протестирован термостат с сигнатурой `_TZE204_aoclfnxz`. Устранена проблема с обновлением OTA.
- 1.0.03a
	- ПреРелиз.
- 1.0.04
	- Добавлен термостат с сигнатурой `_TZE204_edl8pz1k`. 
	- Добавлены функции callback локальных команд в структуру DataPoint'ов.
	- Добавлен `watchdog`.
	- Изменено формирование zb_modelId. 
		> Теперь при обновление на кастомную прошивку, термостаты с разными сигнатурами, но по сути являющиеся одинковыми устройствами, будут получать одинаковое групповое имя, не зависимо от сигнатуры.
		
	- Изменены коверторы z2m, теперь это всего два файла. 
		> Один для термостата с оригинальной прошивкой, второй для уже термостата с кастомной прошивкой. Что-то менять в них не нужно.


		