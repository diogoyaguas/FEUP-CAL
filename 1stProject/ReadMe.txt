Projeto realizado maioritariamente com o IDE Clion, uma vez que com o Visual Studio havia erros de compila��o devido
aos ficheiros fornecidos no moodle (graphiewer e connection).

Para o programa compilar direito neste IDE, � necess�rio verificar se o ficheiro GraphViewerController
est� dentro da pasta cmake-build-debug. Se n�o estiver, � necess�rio coloc�-lo l�.

No entanto, j� � poss�vel compilar no Visual Studio ap�s alguns ajustes.
Para compilar o programa no Visual Studio, � necess�rio que o GraphViewerController esteja na pasta acima do src, junto da solu��o do projeto.
Al�m disso, no projecto, tem de ir a Properties->Linker->Command Line e escrever "ws2_32.lib" (sem as aspas) dentro de "Additional Options". 
fa�a isto para ambas as configura��es (Release and Debug) (No canto superior esquerdo para mudar as "Configura��es").

Importante: O path dos ficheiros e imagem deve de ser alterado se o IDE escolhido for o Clion.
Para tal deve-se substituir "src/lines.txt", por "../src/lines.txt", "src/stations.txt" por "../src/stations.txt" e "res/station.png" por "../res/station.png"


### Team Members
Diogo Filipe da Silva Yaguas<br>
* Student Number: 201606165
* E-Mail: 201606165@fe.up.pt

Joana Maria Cerqueira da Silva
* Student Number: 201208979
* E-Mail: up201208979@fe.up.pt

Ricardo Manuel Ferreira Teixeira
* Student Number: 201604911
* E-Mail: up201604911@fe.up.pt