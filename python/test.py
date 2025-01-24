import numpy as np
import matplotlib.pyplot as plt
import pyserial as ps

for i in range(1,20):
    print(23)



def can_write(u,m,e) : 
    if(u.Metier == "Medecin") :
            grantReadAccess()
    elif(u.Metier == "Infirmieres"):
        if(m.Clinique_Base_De_Donnee == u.Nom_De_La_Clinique_utilisateur):
            grantReadAccess()
        else:
            dontGrantReadAccess()
    else:
        dontGrantReadAccess()
    


R2 : can\_write(u,m,e)