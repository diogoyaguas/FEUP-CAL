Projeto realizado maioritariamente com o IDE Clion, uma vez que com o Visual Studio havia erros de compilação devido
aos ficheiros fornecidos no moodle (graphiewer e connection).

Para o programa compilar direito neste IDE, é necessário verificar se o ficheiro GraphViewerController
está dentro da pasta cmake-build-debug. Se não estiver, é necessário colocá-lo lá.

No entanto, já é possível compilar no Visual Studio após alguns ajustes.
Para compilar o programa no Visual Studio, é necessário que o GraphViewerController esteja na pasta acima do src, junto da solução do projeto.
Além disso, no projecto, tem de ir a Properties->Linker->Command Line e escrever "ws2_32.lib" (sem as aspas) dentro de "Additional Options". 
faça isto para ambas as configurações (Release and Debug) (No canto superior esquerdo para mudar as "Configurações").

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