
$(document).ready(function() {

 	$('.scrollTo').click( function() {
 		// La fonction attr() permet de récupérer le contenu de la valeur de href dans ce cas là
    	
    	var page = $(this).attr('href');
    	
    	// La fonction offset permet de recupérer la position de l'objet possdans la class srollTo

      	$('html, body').animate( { scrollTop: $(page).offset().top }, "slow");
      	return false;
    });
});
