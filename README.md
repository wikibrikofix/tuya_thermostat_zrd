# Tuya Thermostat for Floor Heating Zigbee with custom firmware

**Tuya Thermostat model**

	"_TZE204_u9bfwha0"
	"_TZE204_aoclfnxz"

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/TYBAC-006.png"/>

**Автор не несет никакой отвественности, если вы, воспользовавшись этим проектом, превратите свой умный термостат в полоумный.**

Проверялись только термостаты перечисленные выше. Если у вас другая сигнатура, лучше не заливать, не проверив на совпадение датапоинтов.

Проверялся только в zigbee2mqtt.

## Зачем. 

Чтобы не спамил в сеть. Именно этот экземпляр посылал 25 пакетов каждые 8 секунд.

## Что получилось. 

**About**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_about.jpg"/>

**Exposes**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_exposes.jpg"/>

**Reporting**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_reporting.jpg"/>


## Как обновить.

Сначала подключаем к z2m два внешних [конвертора](https://github.com/slacky1965/tuya_thermostat_zrd/tree/main/zigbee2mqtt/convertors) `tuya_thermostat_orig.js` и `tuya_thermostat_model1.js`. Первый активирует OTA в z2m для термостата с прошивкой от Tuya. Второй - для термостата с кастомной прошивкой.

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

Далее перегружаем z2m. И видим у нас новое устройство (надеюсь до всего этого термостат уже был в сети и виден в z2m).

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

Более развернутое описание [тут](https://habr.com/ru/articles/864740)

## История версий
- 1.0.01	- Начало.
- 1.0.02	- Релиз.
- 1.0.03	- Устраненая проблема с возможностью установить температуру нагрева выше порога, заданного в maxHeatSetpoint. Откорректирован конвертор на предмет проброса термостата в Home Assistant. Добавлены функции callback в структуру DataPoint'ов. Протестирован термостат с сигнатурой `_TZE204_aoclfnxz`.



