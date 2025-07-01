<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
</head>
<body>
  <h1>Proyecto Final - Comedero Automático con Arduino</h1>
  <p><strong>Materia:</strong> Laboratorio 1</p>
  <p><strong>Carrera:</strong> Ingeniería Informática</p>
  <p><strong>Universidad:</strong> Universidad Blas Pascal</p>
  <p><strong>Fecha:</strong> 01/07/2025</p>

  <h2>Descripción del Proyecto</h2>
  <p>Este proyecto consiste en el desarrollo de un <strong>comedero automático para mascotas</strong>, utilizando una placa Arduino UNO como cerebro principal. Fue desarrollado como proyecto final para la materia <strong>Laboratorio 1</strong> de la carrera de Ingeniería Informática en la <strong>Universidad Blas Pascal</strong>. El objetivo principal fue aplicar conocimientos de electrónica digital y programación embebida en un producto funcional, con interfaz intuitiva y configurable.</p>

  <h2>Contenidos del Repositorio</h2>
  <p>Este repositorio incluye:</p>
  <ul>
    <li><strong>Código Arduino:</strong> Código principal que permite configurar los horarios de alimentación y la cantidad de raciones mediante un encoder rotativo. Controla el reloj interno, muestra la hora en un display y activa un servo motor para dispensar alimento.</li>
    <li><strong>Esquema del Circuito:</strong> Instrucciones detalladas para montar el circuito en Tinkercad, incluyendo conexiones entre la pantalla, RTC, servo, encoder y botón.</li>
    <li><strong>Diagrama de Flujo:</strong> Explicación de los modos de funcionamiento del sistema (modo normal, configuración de hora, configuración de alimentación).</li>
    <li><strong>Manual de Uso:</strong> Descripción paso a paso de cómo operar el comedero, modificar los horarios y activar la alimentación manualmente.</li>
    <li><strong>Informe del Proyecto:</strong> Documento con desarrollo, problemas encontrados, soluciones aplicadas y posibles mejoras futuras.</li>
  </ul>

  <h2>Componentes Utilizados</h2>
  <ul>
    <li>Arduino UNO</li>
    <li>Módulo RTC DS1302</li>
    <li>Pantalla LCD 16x2 con módulo I2C (dirección 0x27)</li>
    <li>Servo motor SG90</li>
    <li>Encoder rotativo con botón integrado</li>
    <li>Botón pulsador adicional para alimentación manual</li>
    <li>Resistencias de 10kΩ (para pull-up del encoder si es necesario)</li>
    <li>Cables de conexión</li>
    <li>Protoboard o placa perforada para armado</li>
  </ul>

  <h2>Funciones Destacadas</h2>
  <ul>
    <li>Visualización de hora actual con segundos</li>
    <li>Configuración de hora del sistema mediante el encoder</li>
    <li>Programación de dos horarios diarios de alimentación</li>
    <li>Selección de número de raciones (entre 1 y 10)</li>
    <li>Modo manual de dispensado</li>
    <li>Interfaz sencilla en pantalla LCD con mensajes claros</li>
    <li>Almacenamiento de configuración en EEPROM</li>
  </ul>
</body>
</html>
