/* c401.c: **********************************************************}
{* Téma: Rekurzivní implementace operací nad BVS
**                                         Vytvořil: Petr Přikryl, listopad 1994
**                                         Úpravy: Andrea Němcová, prosinec 1995
**                                                      Petr Přikryl, duben 1996
**                                                   Petr Přikryl, listopad 1997
**                                  Převod do jazyka C: Martin Tuček, říjen 2005
**                                         Úpravy: Bohuslav Křena, listopad 2009
**                                                 Karel Masařík, říjen 2013
**                                                 Radek Hranický 2014-2018
**
** Implementujte rekurzivním způsobem operace nad binárním vyhledávacím
** stromem (BVS; v angličtině BST - Binary Search Tree).
**
** Klíčem uzlu stromu je jeden znak (obecně jím může být cokoliv, podle
** čeho se vyhledává). Užitečným (vyhledávaným) obsahem je zde integer.
** Uzly s menším klíčem leží vlevo, uzly s větším klíčem leží ve stromu
** vpravo. Využijte dynamického přidělování paměti.
** Rekurzivním způsobem implementujte následující funkce:
**
**   BSTInit ...... inicializace vyhledávacího stromu
**   BSTSearch .... vyhledávání hodnoty uzlu zadaného klíčem
**   BSTInsert .... vkládání nové hodnoty
**   BSTDelete .... zrušení uzlu se zadaným klíčem
**   BSTDispose ... zrušení celého stromu
**
** ADT BVS je reprezentován kořenovým ukazatelem stromu (typ tBSTNodePtr).
** Uzel stromu (struktura typu tBSTNode) obsahuje klíč (typu char), podle
** kterého se ve stromu vyhledává, vlastní obsah uzlu (pro jednoduchost
** typu int) a ukazatel na levý a pravý podstrom (LPtr a RPtr). Přesnou definici typů
** naleznete v souboru c401.h.
**
** Pozor! Je třeba správně rozlišovat, kdy použít dereferenční operátor *
** (typicky při modifikaci) a kdy budeme pracovat pouze se samotným ukazatelem
** (např. při vyhledávání). V tomto příkladu vám napoví prototypy funkcí.
** Pokud pracujeme s ukazatelem na ukazatel, použijeme dereferenci.
**/

#include "c401.h"
int solved;

void BSTInit (tBSTNodePtr *RootPtr) {
/*   -------
** Funkce provede počáteční inicializaci stromu před jeho prvním použitím.
**
** Ověřit, zda byl již strom předaný přes RootPtr inicializován, nelze,
** protože před první inicializací má ukazatel nedefinovanou (tedy libovolnou)
** hodnotu. Programátor využívající ADT BVS tedy musí zajistit, aby inicializace
** byla volána pouze jednou, a to před vlastní prací s BVS. Provedení
** inicializace nad neprázdným stromem by totiž mohlo vést ke ztrátě přístupu
** k dynamicky alokované paměti (tzv. "memory leak").
**
** Všimněte si, že se v hlavičce objevuje typ ukazatel na ukazatel.
** Proto je třeba při přiřazení přes RootPtr použít dereferenční operátor *.
** Ten bude použit i ve funkcích BSTDelete, BSTInsert a BSTDispose.
**/

	*RootPtr = NULL; //nastavím ukazatel na NULL

}

int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content)	{
/*  ---------
** Funkce vyhledá uzel v BVS s klíčem K.
**
** Pokud je takový nalezen, vrací funkce hodnotu TRUE a v proměnné Content se
** vrací obsah příslušného uzlu.´Pokud příslušný uzel není nalezen, vrací funkce
** hodnotu FALSE a obsah proměnné Content není definován (nic do ní proto
** nepřiřazujte).
**
** Při vyhledávání v binárním stromu bychom typicky použili cyklus ukončený
** testem dosažení listu nebo nalezení uzlu s klíčem K. V tomto případě ale
** problém řešte rekurzivním volání této funkce, přičemž nedeklarujte žádnou
** pomocnou funkci.
**/

	if(RootPtr != NULL){ //prázdný strom nemá smysl procházet
		if (RootPtr->Key == K){ //když najdu uzel odpovídající klíči
			*Content = RootPtr->BSTNodeCont; //nastavím hodnotu
			return TRUE; //vracím true
		}
		else if(K < RootPtr->Key){ //když nenajdu a aktuální klíč je menší než ten, co hledám
			if (BSTSearch(RootPtr->LPtr, K, Content)){//pokračuju rekurzivně v levé větvi
				return TRUE;//když najdu, vracím TRUE
			}
			else{
				return FALSE;//nenajdu, vracím FALSE
			}
		}
		else if(K > RootPtr->Key){
			if (BSTSearch(RootPtr->RPtr, K, Content)){//pokračuju rekurzivně v pravé větvi
				return TRUE;//když najdu, vracím TRUE
			}
			else{
				return FALSE;//nenajdu, vracím FALSE
			}
		}
	}
	else{
	}

	return 	FALSE; //když je strom prázdný, vracím FALSE

}


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content)	{
/*   ---------
** Vloží do stromu RootPtr hodnotu Content s klíčem K.
**
** Pokud již uzel se zadaným klíčem ve stromu existuje, bude obsah uzlu
** s klíčem K nahrazen novou hodnotou. Pokud bude do stromu vložen nový
** uzel, bude vložen vždy jako list stromu.
**
** Funkci implementujte rekurzivně. Nedeklarujte žádnou pomocnou funkcsi.
**
** Rekurzivní implementace je méně efektivní, protože se při každém
** rekurzivním zanoření ukládá na zásobník obsah uzlu (zde integer).
** Nerekurzivní varianta by v tomto případě byla efektivnější jak z hlediska
** rychlosti, tak z hlediska paměťových nároků. Zde jde ale o školní
** příklad, na kterém si chceme ukázat eleganci rekurzivního zápisu.
**/

	if (*RootPtr == NULL) {//ukazatel je prázdný - jsme na koncovém lstu nebo na hlavní uzlu
		(*RootPtr) = malloc(sizeof(struct tBSTNode));//alokuji místo pro nový prvek, bez zavorek kolem RootPtr error!
		(*RootPtr)->Key = K;//klíč
		(*RootPtr)->BSTNodeCont = Content;//nastaívvm obsah
		(*RootPtr)->LPtr = NULL;//ukazatele leva/pravá na NULL
		(*RootPtr)->RPtr = NULL;
	}
	else{//jinak
		if (K < (*RootPtr)->Key){//klic co hledam je mensi
			BSTInsert(&(*RootPtr)->LPtr, K, Content);//jdu do leve vetve
		}
		else if(K > (*RootPtr)->Key){//klic je vetsi
			BSTInsert(&(*RootPtr)->RPtr, K, Content);//jdu do prave vetve
		}
		else{//klic je stejny
			(*RootPtr)->BSTNodeCont = Content; //prepisu jeho hodnotu
		}
	}

}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {
/*   ------------------
** Pomocná funkce pro vyhledání, přesun a uvolnění nejpravějšího uzlu.
**
** Ukazatel PtrReplaced ukazuje na uzel, do kterého bude přesunuta hodnota
** nejpravějšího uzlu v podstromu, který je určen ukazatelem RootPtr.
** Předpokládá se, že hodnota ukazatele RootPtr nebude NULL (zajistěte to
** testováním před volání této funkce). Tuto funkci implementujte rekurzivně.
**
** Tato pomocná funkce bude použita dále. Než ji začnete implementovat,
** přečtěte si komentář k funkci BSTDelete().
**/


	if(RootPtr != NULL){//prazdny list nema smysl prochazet
		if ((*RootPtr)->RPtr != NULL){//zkontroluju, zda se napravo jeste vubec neco nachazi
			ReplaceByRightmost(PtrReplaced, &(*RootPtr)->RPtr); //rekurzivne volam fci
		}
		else{ //kdyz uz se tam nic nenachazi
			PtrReplaced->Key = (*RootPtr)->Key;
			PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
			tBSTNodePtr uzel;//malloc
      uzel = (*RootPtr); //
			(*RootPtr) = (*RootPtr)->LPtr; //smazu uzel...
			free(uzel);
		}
	}
	else{//nema smysl
	}

}

void BSTDelete (tBSTNodePtr *RootPtr, char K) 		{
/*   ---------
** Zruší uzel stromu, který obsahuje klíč K.
**
** Pokud uzel se zadaným klíčem neexistuje, nedělá funkce nic.
** Pokud má rušený uzel jen jeden podstrom, pak jej zdědí otec rušeného uzlu.
** Pokud má rušený uzel oba podstromy, pak je rušený uzel nahrazen nejpravějším
** uzlem levého podstromu. Pozor! Nejpravější uzel nemusí být listem.
**
** Tuto funkci implementujte rekurzivně s využitím dříve deklarované
** pomocné funkce ReplaceByRightmost.
**/

	tBSTNodePtr uzel;
	uzel = NULL;

	if (*RootPtr == NULL){ //když je strom prázdný
		return; //ukončím rekurzi
	}
	else{
		if((*RootPtr)->Key == K){//heureka, nalezli jsme uzel s pozadovanym klicem
			if (((*RootPtr)->LPtr != NULL)&&((*RootPtr)->RPtr != NULL)){//uzel ma oba dva podstromy //chybka nejaka!
				ReplaceByRightmost((*RootPtr), &(*RootPtr)->LPtr); // uvolnim nejpravejsi
			}
			else if ((*RootPtr)->LPtr != NULL){//uzel ma jen levou vetev
				uzel = *RootPtr;
				*RootPtr = (*RootPtr)->LPtr;
				free(uzel);
			}
			else if ((*RootPtr)->RPtr != NULL){//uzel ma jen pravou vetev
				uzel = *RootPtr;
				*RootPtr = (*RootPtr)->RPtr;
				free(uzel);
			}
			else{//uzel nema zadnou vetev
				free(*RootPtr);
				*RootPtr = NULL;

			}
		}
		else{//nenalezli jsme uzel odpovidajici klici, hldam v dalsi vetvi
			if (K < (*RootPtr)->Key){
				BSTDelete(&(*RootPtr)->LPtr, K);
			}
			else if(K > (*RootPtr)->Key){
				BSTDelete(&(*RootPtr)->RPtr, K);
			}
		}
	}

}

void BSTDispose (tBSTNodePtr *RootPtr) {
/*   ----------
** Zruší celý binární vyhledávací strom a korektně uvolní paměť.
**
** Po zrušení se bude BVS nacházet ve stejném stavu, jako se nacházel po
** inicializaci. Tuto funkci implementujte rekurzivně bez deklarování pomocné
** funkce.
**/

	if(*RootPtr != NULL){//jen pri neprazdenm stromu
		BSTDispose(&(*RootPtr)->RPtr);
		BSTDispose(&(*RootPtr)->LPtr);
		free(*RootPtr);
		*RootPtr = NULL;
		return;
	}

}

/* konec c401.c */
