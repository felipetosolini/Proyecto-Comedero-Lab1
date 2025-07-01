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
  <p>Este proyecto consiste en el desarrollo de un <strong>comedero automático para mascotas</strong>, utilizando una placa Arduino UNO como cerebro principal. Fue desarrollado como proyecto final para la materia <strong>Laboratorio 1</strong> de la carrera de Ingeniería Informática en la <strong>Universidad Blas Pascal</strong>. El objetivo principal fue aplicar conocimientos de electrónica digital y programación en un producto funcional, con interfaz intuitiva y configurable.</p>

<h2>Contenidos del Repositorio</h2>
<p>Este repositorio incluye:</p>
<ul>
  <li><strong>Código Arduino:</strong> Código fuente completo que permite controlar el funcionamiento del comedero automático. Permite configurar horarios, cantidad de raciones, visualizar la hora en tiempo real y controlar el servo motor para la dispensación de comida.</li>

  <li><strong>Interfaz en Pantalla LCD:</strong> Implementación de un sistema de menús minimalista con encoder rotativo, que permite ajustar fácilmente la hora del sistema, los horarios de comida y las raciones a dispensar.</li>

  <li><strong>Almacenamiento en EEPROM:</strong> Se utiliza la memoria EEPROM interna del Arduino para guardar la configuración del usuario (horarios y raciones), evitando la necesidad de reconfigurar el dispositivo cada vez que se reinicia.</li>

  <li><strong>Esquema del Circuito:</strong> Diagramas de conexión entre los componentes electrónicos utilizados, incluyendo la pantalla LCD I2C, el módulo RTC DS1302, el servo motor, el encoder rotativo y el botón de alimentación manual.</li>

  <li><strong>Diseño del Chasis:</strong> Diseño impreso en 3D que sirve como estructura para alojar el sistema electrónico del comedero. Permite sujetar el servo y direccionar la caída del alimento hacia el recipiente.</li>

  <li><strong>Tutorial y Guía del Proyecto:</strong> Guía paso a paso sobre cómo armar el circuito, cargar el programa, ajustar la hora y programar las comidas.</li>

  <li><strong>Informe del Proyecto:</strong> Documento detallado sobre el desarrollo del sistema, los desafíos encontrados, decisiones técnicas tomadas, pruebas realizadas y mejoras futuras.</li>
</ul>


  <h2>Componentes Utilizados</h2>
  <ul>
    <li>Arduino UNO</li>
    <li>Módulo RTC DS1302</li>
    <li>Pantalla LCD 16x2 con módulo I2C (dirección 0x27)</li>
    <li>Servo motor SG90</li>
    <li>Encoder rotativo con botón integrado</li>
    <li>Botón pulsador adicional para alimentación manual</li>
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
