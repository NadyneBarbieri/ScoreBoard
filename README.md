# ScoreBoard
Trabalho realizado para um dos professores da Fiap com o objetivo de nos avaliar. Consiste em criar um scoreboard 

Antes dos requisitos, vamos ver algumas regras de pontuação do jogo de Voleibol:
Quadra
Para que uma das equipes ganhe um Set, ela precisa alcançar 25 pontos e ter 2 pontos de diferença para a equipe rival. (se estiver 24 x 24, para ganhar o Set uma das equipes tem que fazer 26 x 24, ou 27 x 25, e assim por diante);
Para que uma das equipes ganhe a partida, precisa ter 3 sets ganhos;
Caso a partida estiver empatada em 2 Sets para cada equipe, um quinto e último Set será disputado, mas com limite de 15 pontos, mantendo-se, para confirmar a vitória, a diferença de 2 pontos entre as equipes (se estiver 14 x 14, para ganhar o Set e o jogo uma das equipes tem que fazer 16 x 14, ou 17 x 15, e assim por diante). Este Set denominando-se este Tiebreake;
Durante o Tiebreak, quando uma das equipes chegar ao ponto 8, haverá a troca de lados na quadra.
Areia
Para que uma das equipes ganhe um Set, ela precisa alcançar 21 pontos e ter 2 pontos de diferença para a equipe rival. (se estiver 20 x 20, para ganhar o Set uma das equipes tem que fazer 22 x 20, ou 23 x 21, e assim por diante);
Para que uma das equipes ganhe a partida, precisa ter 2 Sets ganhos;
Caso a partida estiver empatada em 1 Set para cada equipe, um terceiro e último Set será disputado, com limite de 15 pontos, mantendo-se, para confirmar a vitória, a diferença de 2 pontos entre as equipes (se estiver 14 x 14, para ganhar o Set e o jogo uma das equipes tem que fazer 16 x 14, ou 17 x 15, e assim por diante). Este Set denominando-se este Tiebreake;
Durante o Tiebreak, quando a soma da pontuação atingir um múltiplo de 7 pontos, haverá a troca de lados. Assim, sempre que a soma dos pontos for 7, 14, 21, 28, etc., as duplas trocarão de lado.
O projeto pode ser desenvolvido no simulador Wokwi, tendo como base os seguintes requisitos:

1 - Materiais:
02 Displays duplos de 7 segmentos e Anodo comum;
02 Displays simples de 7 segmentos e Anodo comum;
01 Display LCD I2C 16 x 2;
05 Botões Push (2 vermelhos e 2 verdes, um conjunto para cada equipe e um de outra cor para reset do sistema);
01 Módulo Encoder Rotativo KY-040;
O controlador (Arduinos ou ESP32), bem como a linguagem fica a critério de cada grupo.


2 - Funcionamento
Ao ligar o circuito, deverá aparecer no LCD instruções para que o usuário rode o encoder e escolha a opção desejada.
Ao girar o encoder, devem aparecer 2 opções a serem escolhidas usando o próprio botão nativo do encoder:
a. Quadra;
b. Areia.

Com isso quem estiver fazendo a somatória dos pontos, fará uso dos botões. (Verde para adicionar um ponto e vermelho para subtrair).

Toda a lógica de finalização dos Sets, inclusive o Tiebreak deve ser automática e de acordo com a modalidade escolhida (quadra ou areia).
A cada final de Set, essa mensagem deve ser informada por 30 segundos no Display LCD.
As trocas de lado durante o Tiebreak também deve ser automáticas e também estar no Display LCD por 30 segundos.

Como opcional, pode-se inserir 2 leds (um pra cada equipe), para indicar qual time vai sacar.
DICA: Use a biblioteca SEVSEG! 
<img src="https://i.ibb.co/nLkypMw/Captura-de-tela-2024-01-15-182636.png" alt="Captura-de-tela-2024-01-15-182636" border="0">
