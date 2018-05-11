app.factory('tradService', function () {
    var serv = {};

    serv.translateTable = {
        'user': {
            'USER_EMPTY': 'Tous les champ sont vide',
            'USER_CREATE_SUCCESS': 'Utilisateur crée avec succée',
            'USERNAME_EMPTY': 'Nom d\'utilisateur vide',
            'PASSWORD_EMPTY': 'Le champ mot de passe est vide',
            'PASSWORD_CONFIRM_EMPTY': 'Confirmation du mot de passe vide',
            'EMAIL_EMPTY': 'Le champs email est vide',
            'INVALID_EMAIL': 'Le champs email est invalide',
            'USER_ALREADY_EXIST': 'L\'utilisateur existe déjà',
            'PASSWORD_DIFFERENT': 'Les mots de passe sont différents',
            'LOGIN_SUCCESS': 'Connexion avec succée',
            'LOGIN_FAIL': 'Utilisateur ou mot de passe incorret',
            'USER_LOGOUT': 'Déconnexion avec succée',
            'MUST_LOGGED': 'Vous devez être logger pour accéder à ce service',
            'NOT_LOGGED': 'Non conncecté',
            'INVALID_TOKEN': 'Token invalide',
        },
        'todo': {
            'TASKNAME_EMPTY': 'Tache vide',
            'INVALID_TOKEN': 'Token d\'identification invalide',
            'NO_TOKEN': 'Vous devez être logger pour accéder à ce service'
        }
    };

    serv.get = function (cat, key) {
        return serv.translateTable[cat][key];
    }

    return serv;
});
