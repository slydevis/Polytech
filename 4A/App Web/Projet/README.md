# Prérequis

* MongoDB installé
* Node.JS > 8.0 installé
* Ionic installé
* Cordova installé

# Configuration

Afin de pouvoir ce connecter à la base de donnée MongoDB il faut configurer le serveur. Pour ce faire il faut éditer le fichier `config.js` dans le dossier `Serveur`. Par défaut la connection à la base de donnée ce fera en local sur le port `27017`. Le fichier de configuration sera donc :

``` js
    'port': 8090, // Port d'écoute pour le serveur
    'database': {
        'host': 'localhost', // Adresse IP de la base de donnée
        'port': 27017, // Port d'écoute du service mongoDB
        'name': 'todoList' // Nom de la base de donnée
    }
```

Maintenant vous pouvez lancer le service MongoDB (si il ne tourne pas déjà) :

* Sur Windows lancez en administrateur l'executable où vous avez installé mongoDB, par exemple :
```
C:\Program Files\MongoDB\Server\3.6\bin\mongod.exe
```
* Sur Linux dans un terminal :
```
mongo
ou 
mongod
```

# Démarrer l'application Web

Par défaut l'application web est disponible une fois lancé à l'adresse suivante : [http://localhost:8090](http://localhost:8090/)

> /!\ Avant de commencer il faut lancer le service MongoDB

## Sur Windows/Linux

1. Ouvrir un terminal et placez vous dans le dossier `Serveur`
2. Installez les dépendances avec la commande suivante : `npm install`
3. Lancez le serveur avec la comande : `node server.js`
4. L'application Web sera désormais disponible à l'adresse [http://localhost:8090](http://localhost:8090/)

## Sur Visual Studio Code

> /!\ Avant de commencer il faut executér un `npm install` dans le dossier pour installer toutes les dépendances nécessaire

1. Ouvrir dans Visual Studio Code le dossier `Serveur`
2. Appuyez sur `F5` pour lancer le serveur
3. L'application Web sera désormais disponible à l'adresse [http://localhost:8090](http://localhost:8090/)

# Démarrer l'application Mobile

>  /!\ Avant de lancer l'application mobile il faut que l'application Web soit en service ainsi que le service MongoDB soit lancé

Par défaut l'application mobile sera disponible à l'adresse suivante : [http://localhost:8100](http://localhost:8100/)

## Sur Linux/Windows

1. Ouvrir un terminal dans le dossier App_Mobile
2. Installez toutes les dépendances avec la commande `npm install`
3. Executez la commande `ionic serve`
4. L'application mobile sera disponible à l'adresse [http://localhost:8100](http://localhost:8100/)

## Sur Visual Studio Code

> /!\ Avant de commencer il faut executér un `npm install` dans le dossier pour installer toutes les dépendances nécessaire

1. Ouvrir dans Visual Studio Code le dossier `App_Mobile`
2. Allez dans la rebrique débogueur (`CTRL+MAJ+D`) dans les onglets à gauche et ensuite sélectionnez la configuration dans la liste déroulante : `Serve to the browser (ionic serve)`
> Si la liste déroulante est vide cliquez sur le petit écrou à droite et séléctionnez l'environnement Cordova
3. Appuyez sur la flèche verte ou sur la touche `F5`
4. Un navigateur va s'ouvrir vous pouvez ensuite accéder à l'application mobile ou avec l'adresse [http://localhost:8100](http://localhost:8100/)