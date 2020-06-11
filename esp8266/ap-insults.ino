/*Here have some code
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal

* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* (C) other authors (Scott borrowed insults() from the previous sketch)
* (C) 2020 Scott Edwards - https://github.com/supaplextor
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  Serial.println();
}

String insult(){
  char *firstV[50] = {"Artless ","Bawdy ","Beslubbering ","Bootless ","Churlish ","Cockered ","Cloouted ","Craven ","Currish ","Dankish ","Dissembling ","Droning ","Errant ","Fawning ","Fobbing ","Forward ","Frothy ","Gleekish ","Goatish ","Gorbellied ","Impertinent ","Infecious ","Jarring ","Joggerhead ","Lumpish ","Mammering ","Mangled ","Mewling ","Paunchy ","Pribbling ","Punking ","Puny ","Qualling ","Rank ","Reeky ","Rougish ","Ruttish ","Saucy ","Spleeny ","Spongy ","Surly ","Tottering ","Unmuzzled ","Vain ","Venomed ","Villainous ","Warped ","Wayward ","Weedy ","Yeasty "};
  char *secondV[50] = {"base-court ","bat-forling ","beef-witted ","beetle-headed ","boil-brained ","clapper-clawed ","clay-brained ","common-kissing ","crook-pated ","dismal-dreaming ","dizzy-eyed ","doghearted ","dread-bolted ","earth-vexing ","elf-skinned ","fat-kidneyed ","fen-sucking ","flap-mouthed ","fly-bitten ","folly-fallen ","fool-born ","ill-gorged ","guts-griping ","half-faced ","hasty-witted ","hedge-born ","hell-hated ","idle-headed ","ill-breeding ","ill-nurtured ","knotty-pated ","milk-livered ","motley-minded ","onion-eyed ","plume-puckered ","pottle-deep ","pox-marked ","reeling-ripe ","rough-hewn ","rude-growing ","rump-fed ","shard-born ","sheep-biting ","spur-galled ","swag-bellied ","tardy-gaited ","tickle-brained ","toad-spotted ","unchin-snoted ","weatherbitten "};
  char *thirdV[49] = {"apple-John","baggage","barnacle","bladder","boar-pig","bugbear","bum-bailey","canket-blossom","clack-dish","clotpole","coxcomb","codpieve","death-token","dewberry","flap-dragon","flirt-gill","foot-licker","futilarrian","giglet","gudgeon","haggard","harpy","hedge-pig","horn-beast","hugger-mugger","joithead","lewduster","lout","maggot-pie","malt-worm","mammet","measle","minnow","miscreant","moldwarp","mumble-news","nut-hook","pigeon-egg","pignut","puttock","pumpion","ratsbane","scut","skainsmate","strumpot","varlot","vassal","wheyface","wagtail"};
  
  long A = random(0,50);
  long B = random(0,50);
  long C = random(0,49);
  String phrase = firstV[A];
  phrase += secondV[B];
  phrase += thirdV[C];
  return phrase;
}

void loop()
{
  String ssid = insult();
  boolean result = WiFi.softAP(ssid, "");
  Serial.println("WiFi.softAP("+ssid+"\",\"\");");
}
