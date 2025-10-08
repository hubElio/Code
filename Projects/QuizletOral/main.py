# audio_quizlet.py
from gtts import gTTS
from pydub import AudioSegment
from pydub.generators import Silence

# === Ton texte brut (tu peux aussi le lire depuis un fichier) ===
texte = """
Alabama
Montgomery Mouvement droits civiques
Ancienne culture cotonnière
Barbecue à l’Alabama white sauce
Football universitaire (Crimson Tide)
Alaska
Aurores boréales
Pétrole
Saumon grillé
Arizona
Grand Canyon
Désert de Sonora
Culture amérindienne (Navajo, Hopi)
Chimichanga (burrito frit)
Arkansas
Montagnes Ozark 
Diamants (Crater of Diamonds)
Possum Pie (tarte à étages chocolat-crème)
Johnny Cash,Bill Clinton
(almost nuclear explosion, most racist state (kkk), bible belt (fear of god))
Californie
plages de Malibu, séismes
Hollywood, Silicon Valley
Fish tacos ou avocado toast
Caroline du Nord
Bancs de sable (Outer Banks)
tabac
Naissance de l'aviation (frères Wright)
Carolina Pulled Pork BBQ
Caroline du Sud
Myrtle Beach
hopsewee plantation Georgestown
Shrimp and Grits
Colorado
Montagnes Rocheuses, 
stations de ski (Aspen, Vail), 
Rocky Mountain Oysters (testicules de taureau frits)
(cannabis légal)
Connecticut
Université de Yale, 
architecture coloniale, berceau de l’industrie horlogère.
Hot lobster roll (lobster roll chaud au beurre)
Dakota du Nord
Grandes plaines, 
réserves pétrolières (Bakken), 
bisons
Knoephla Soup (soupe de boulettes germano-russe)
"""

# === Traitement du texte ===
lines = [l.strip() for l in texte.split("\n") if l.strip()]
etats = []
bloc = []
for line in lines:
    if not line[0].islower():  # suppose qu'un État commence par une majuscule
        if bloc:
            etats.append(bloc)
        bloc = [line]
    else:
        bloc.append(line)
if bloc:
    etats.append(bloc)

# === Création de l'audio ===
final_audio = AudioSegment.silent(duration=1000)

for bloc in etats:
    etat = bloc[0]
    faits = bloc[1:]
    
    # Lecture du nom de l'État
    tts = gTTS(etat, lang='fr')
    etat_audio = AudioSegment.from_file(tts.save(f"{etat}.mp3") or f"{etat}.mp3")
    final_audio += etat_audio + Silence(duration=1500)
    
    # Lecture des faits
    for f in faits:
        tts = gTTS(f, lang='fr')
        f_audio = AudioSegment.from_file(tts.save(f"temp.mp3") or "temp.mp3")
        final_audio += f_audio + Silence(duration=1200)

# === Export du fichier final ===
final_audio.export("usa_quiz_audio.mp3", format="mp3")
print("✅ Fichier audio généré : usa_quiz_audio.mp3")