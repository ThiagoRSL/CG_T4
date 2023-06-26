Instruções:
    - Para jogar é só iniciar o jogo.
    - Ele se adapta ao tamanho da tela (apresenta responsividade da interface)
    - Ao atingir o final da curva (grande quadrado amarelo), passa de nível.
    - Curvas são geradas aleatóriamente
    - Dicas para facilitar o Debug:
        + Na função keyboard da main existe uma linha comentada no caso 8 (tecla backspace), que permite que ao pressionar o botão a fase seja atualizada pro próximo nível.

Extras:
- Disparo de rajadas com efeitos visuais bonitos: Particulas adicionadas no deslocamento da nave e dos disparos.
- Simulação da explosão dos inimigos: altera a cor dos elementos para laranja/amarelo (simulando sobreaquecimento).
- Inimigos que se movem na tela com alguma IA: quando o jogador sai do campo de visão do inimigo ele se desloca até próximo ao último ponto
conhecido do jogador. Além disso, euquanto o jogador se afasta os inimigos o perseguem.
- Aspecto visual do jogo, jogabilidade, níveis de dificuldade, inimigos mais fortes a medida
que o tempo passa (Progressão baseada no no Level atual, basicamente existe uma série de valores que escalam com o Level do jogo, listados à seguir):
    + A chance de um grupo mais poderoso de inimigos aparecer é maior.
    + A chance de um inimigo grande (nave com três canhões) aparecer aumenta, estas naves dão mais pontos, possuem mais vida e disparam mais projeteis.
    + O HP dos inimigos aumenta com base no nível da sala, assim como a velocidade deles.
    + O campo de visão dos inimigos aumenta com base no Level até um máximo de 1000, é calculado como 500 + (Level*25).
    + Cada level tem mais pontos de controle nas curvas das laterais, dispostos de maneira à torna-lá mais longa conforme o level aumenta.

FAZER
- Munições especiais que buscam o inimigo calculando trajetórias curvas:
- Power-ups para disparos especiais, ou escudo: poderes que podem ser utilizados com o consumo de energia (barrinha azul), ao pressionar as teclas especiais:
    + Tecla "Espaço": Entra em modo dash, triplicando a velocidade e ignorando o dano de colisão com outras naves mas ainda causando dano à elas.
    + Tecla "X": invoca 4 disparos que perseguem os alvos.
    + No inicio de cada nível a barra de energia é resetada.

Outros Possíveis Extras:
- Mecanismo de Otimização de Renderização: renderiza apenas elementos próximos (aplicável à curvas e personagens), visivel atraves da alteração da constante 
RENDER_DISTANCE no RenderManager.h (é visível a diferença do desempenho nas curvas pela presença de tantos pontos);
- Após o décimo level a nave do jogador recebe um upgrade, aumentando sua vida e energia máxima, além de aumentar o número de canhões.