<style> @import url('https://fonts.googleapis.com/css?family=VT323'); h1{ text-align: center; font-size: 50px; font-family: 'VT323', monospace; } h2{ font-weight: bold; } h3{ font-weight: bold; } img { height: auto; width: 100%; } note { font-weight: lighter; background-color: rgba(100, 100, 100, 0.3); font-style: italic; } p{ text-align: justify; } img{ width: 100%; height: auto; } .center{ width: 20%; height: auto; margin-left: auto; margin-right: auto; display: block; } .half{ width: 50%; height: auto; margin-left: auto; margin-right: auto; } .mini{ width: 30%; height: auto; } </style>

# Sistemes Operatius 2

<img class="center" src="baka.png">

Treballarem amb x86 amb regs de 32 bits.

Registres importants:
- EAX
- EBX
- ESI
- EDI
- ECX
- EBP
- ESP
- EDX

## Mecanismes d'integritat del Sistema Operatiu

### Nivells de privilegi

Fa que els usuaris no tinguin accés al hardware. Les instruccions privilagiades només poden ser executades per l'OS. Es necessaria suport de hardware.

## Vector d'interrupcions

IDT: Interrupt Descriptor Table: 256 entrades

- 0 - 31: Exceptions
- 32 - 47: Masked interrupts
- 48 - 255: Software interrupts (Traps)

El tractament de la excepcio s'hauria de fer en una sola rutina.
