# Led-manage-supervised-By-Watchdog-Timer

This project implements an LED blinking system with a watchdog supervision capability, using various software components to manage different hardware drivers and functionalities. The primary goal is to ensure the LED blinks with precise periodicity while being supervised by a watchdog timer to detect and recover from potential system failures.

## Components

1. **GPIO Management (GPIOMgr)**
    - **GPIO_Init:** Initializes GPIO configuration for the pin controlling the LED.
    - **GPIO_Write:** Writes a specific value (0 or 1) to the pin to control the LED state.

2. **LED Management (LEDMgr)**
    - **LED_Init:** Initializes internal variables of the LED component.
    - **LED_Manage:** Manages LED blinking actions using the GPIO_Write function, called every 10ms to ensure a 500ms on/off cycle for the LED.

3. **Watchdog Driver (WDGDrv)**
    - **WDGDrv_Init:** Configures the watchdog driver with the following features:
        - Sets the maximum timeout value to 50ms.
        - Disables window mode.
        - Enables the early interrupt feature.
        - Activates the watchdog.
    - **WDGDrv_IsrNotification:** Checks if WDGM_MainFunction is not stuck and if WDGM state is OK to refresh the watchdog timer; otherwise, allows the system to reset.

4. **Watchdog Management (WDGM)**
    - **WDGM_Init:** Initializes internal variables of the watchdog management component.
    - **WDGM_MainFunction:** Periodically called every 20ms to supervise the LEDM entity by checking the number of calls to LEDM_Manage within a 100ms period.
    - **WDGM_ProvideSupervisionStatus:** Provides the supervision status of the LEDM entity to the WDGDrv.
    - **WDGM_AlivenessIndication:** Called from LEDM_Manage to confirm timely execution of LEDM_Manage.

5. **Timer Drivers**
    - **Timer1:** Generates an interrupt every 1ms.
    - **Timer2:** Generates an interrupt every 50ms.


## Project Statement

The project implements an LED blinking capability with watchdog supervision. The LED blinking is handled by two software components: LEDMgr and GPIO. GPIO provides initialization and write functions to control the LED. LEDMgr manages the LED blinking actions, ensuring the LED toggles every 500ms, called from a super loop every 10ms.

Watchdog management is handled by WDGDrv and WDGM. WDGDrv implements a complete driver for the watchdog peripheral, configuring it with a 64ms timeout, early interrupt feature, and activation of the watchdog. It uses the WDGDrv_IsrNotification to refresh the watchdog timer based on the status provided by WDGM.

WDGM provides supervision for the LEDM entity, ensuring it functions correctly within a 114ms period. It initializes internal variables, checks the status of LEDM_MainFunction calls, and provides this status to WDGDrv. WDGM also includes an aliveness indication function to confirm timely execution of LEDM_Manage.

The overall system ensures reliable LED blinking with precise timing, supervised by the watchdog timer to detect and recover from any failures, maintaining system robustness and stability.


## Project Scenario
1. **Positive Scenario**

-that checks the periodicity of the LED Blinking, Call of the
LEDM_Manage, Call of the WDGM_MainFunction and refreshment of the WDGDrv.

https://github.com/user-attachments/assets/795f5fdd-1aa4-4044-8cfc-8bf318714d56

2. **Negative Scenario 1**

-that comments the call of the WDGM_MainFunction and checks that
the watchdog reset occurred after 64ms.

https://github.com/user-attachments/assets/40564b76-6664-4421-8426-aac002c3b04e


3. **Negative Scenario 2**

- that comments the call of the WDGM_AlivenessIndication from the
LEDM_Manage while the WDGM_MainFunction is executed periodically and checks that
the watchdog reset occurs after 114ms.

https://github.com/user-attachments/assets/2c175426-9510-4f6a-8b4e-0ff82d2e601a

4. **Negative Scenario 3**

-that changes the periodicity of the call of the LEDM_MainFunction to
be every 5ms and check that watchdog reset occurs after 114ms.

https://github.com/user-attachments/assets/e5e80c70-7dd1-4857-93e3-ecb06ae24cee

