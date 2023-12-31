1\ Pour ce problème, les structures de données clés sont les matrices B, C et la matrice résultante A. En plus de cela, un tampon T est utilisé pour stocker les résultats intermédiaires. Les structures de données nécessaires incluent :

MatB et MatC : Matrices d'entrée remplies de valeurs aléatoires.
MatResult : Matrice résultante A, où les résultats intermédiaires seront stockés.
tampon : Tampon pour stocker les résultats intermédiaires.
vecteur : Tableau pour stocker les indices des éléments à calculer dans la matrice résultante.


2\  Pour protéger l'accès aux données partagées entre les threads, des sémaphores sont utilisés. Dans le code fourni, les sémaphores plein, vide, et mutex sont utilisés pour assurer la synchronisation entre les producteurs et les consommateurs. Le mutex est utilisé pour protéger l'accès aux structures de données partagées, tandis que les sémaphores plein et vide sont utilisées pour synchroniser la production et la consommation dans le tampon

3\ Les principaux risques dans ce type de programme multithread sont liés à la concurrence entre les threads. Certains risques potentiels comprennent :

Conditions de course (race conditions) : Si l'accès aux données partagées n'est pas correctement synchronisé, plusieurs threads pourraient essayer de modifier les mêmes données simultanément, entraînant des résultats imprévisibles.

Dépassement du tampon (buffer overflow) : Si la taille du tampon n'est pas correctement gérée, cela peut conduire à des lectures ou écritures hors limites du tampon.

Blocage mutuel (deadlock) : Si la synchronisation entre les threads n'est pas correctement mise en œuvre, il peut y avoir des situations où les threads se bloquent mutuellement, entraînant un blocage du programme.

Starvation : Certains threads pourraient être bloqués indéfiniment s'ils ne reçoivent jamais l'accès aux ressources partagées.