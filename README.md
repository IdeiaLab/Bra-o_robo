# Braço Robo controlado por Arduino Uno, com uso de: serial, loop for e delay.

O código é um programa para controlar um braço robótico usando um Arduino e servomotores. Ele utiliza a biblioteca Servo para controlar quatro servos, representando diferentes partes do braço robótico. O programa define uma função chamada "movimento" para movimentar gradualmente os servos para posições específicas. Existem variáveis que armazenam os ângulos de posição neutra para cada servo e controles lógicos para garantir que certas ações ocorram apenas uma vez.

O código tem um loop principal que verifica a disponibilidade de dados na porta serial. Se um caractere 'r' for recebido, o braço robótico é movido para a direita, e se for 'g', é movido para a esquerda. A velocidade dos movimentos é controlada por atrasos (delay). Há comentários explicativos em todo o código para facilitar a compreensão. Contudo, vou fazer uma rapida analise de como ele funciona:

1. Configuração Inicial:

    • Definimos quatro objetos do “tipo Servo” para representar os diferentes servomotores do braço: levante, base, avanco e garra.
   
    • Especificamos ângulos de posição neutra para cada servo, armazenados em variáveis de "memória".
   
    • Inicializamos a comunicação serial e configuramos os pinos dos servos.

3. Função de Movimento:

    • Criamos uma função chamada movimento para movimentar gradualmente um servo para uma posição específica.
   
    • A função recebe dois parâmetros: o número do servo (qualServo) e a posição final desejada (pos_final).
   
    • Verificamos a direção do movimento (avanço ou retorno) e movemos o servo com uma velocidade controlada pelo parâmetro velocidade_do_servo.

5. Loop Principal:

    • No loop principal, verificamos se há dados disponíveis na porta serial.
   
    • Se um caractere 'r' for recebido, movemos o braço para a direita; se for 'g', movemos para a esquerda.
   
    • Utilizamos uma variável de controle lógico (Ja_li) para garantir que essas ações ocorram apenas uma vez até que novos dados estejam disponíveis.

7. Considerações Adicionais:

    • Utilizamos a função delay para controlar a velocidade dos movimentos dos servos.
   
    • Os ângulos dos servos são alterados gradualmente para evitar movimentos bruscos.

9. Sugestões para o Usuário:

    • Recomendo ajustar os valores iniciais dos ângulos e a velocidade dos servos conforme necessário.
   
    • Considere substituir os atrasos (delay) por uma abordagem assíncrona usando millis para permitir tarefas simultâneas.
   
    • Lembre-se de que o funcionamento preciso dependerá das características específicas do hardware e da mecânica do seu braço robótico.
