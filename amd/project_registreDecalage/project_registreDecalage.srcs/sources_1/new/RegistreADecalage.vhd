----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/27/2023 07:33:45 PM
-- Design Name: 
-- Module Name: RegistreADecalage - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity RegistreADecalage is
    Port ( reset_top : in STD_LOGIC;
           en_top : in STD_LOGIC;
           clk_top : in STD_LOGIC;
           MODE : in STD_LOGIC_VECTOR (1 downto 0);
           sortie : out STD_LOGIC_VECTOR (3 downto 0));
end RegistreADecalage;



architecture Behavioral of RegistreADecalage is

component bascule
    Port ( reset : in STD_LOGIC;
           en : in STD_LOGIC;
           D : in STD_LOGIC;
           clk : in STD_LOGIC;
           Q : out STD_LOGIC);
end component;

component bascule_v2
    Port ( reset : in STD_LOGIC;
           en : in STD_LOGIC;
           D : in STD_LOGIC;
           clk : in STD_LOGIC;
           Q : out STD_LOGIC);
end component;

component compteur
    Port ( clk_timer : in STD_LOGIC;
           Out_timer : out STD_LOGIC);
end component;

signal sD1,sD2,sD3,sD4,sQ1,sQ2,sQ3,sQ4,reset_top_not,clk_compteur : std_logic;
signal sD1Mode1,sD2Mode1,sD3Mode1,sD4Mode1,sD1Mode0,sD2Mode0,sD3Mode0,sD4Mode0 : std_logic;

begin
compteur_i : compteur port map(clk_top,clk_compteur);


bascule_i_1 : bascule_v2 port map(reset_top,en_top,sD1,clk_compteur,sQ1);
bascule_i_2 : bascule port map(reset_top,en_top,sD2,clk_compteur,sQ2);
bascule_i_3 : bascule port map(reset_top,en_top,sD3,clk_compteur,sQ3);
bascule_i_4 : bascule port map(reset_top,en_top,sD4,clk_compteur,sQ4);

--sD1 <= ((MODE(0) and sQ4) or (not(MODE(0)) and sQ3));
--sD2 <= ((MODE(0) and sQ1) or (not(MODE(0)) and sQ4)); --decalage de deux avec 2nd mode
--sD3 <= ((MODE(0) and sQ2) or (not(MODE(0)) and sQ1));
--sD4 <= ((MODE(0) and sQ3) or (not(MODE(0)) and sQ2));


sD1 <= ((MODE(0) and sQ4) or (not(MODE(0)) and sQ2));
sD2 <= ((MODE(0) and sQ1) or (not(MODE(0)) and sQ3));
sD3 <= ((MODE(0) and sQ2) or (not(MODE(0)) and sQ4));
sD4 <= ((MODE(0) and sQ3) or (not(MODE(0)) and sQ1));





sortie(0) <=((MODE(1) and sD1) or (not(MODE(1)) and not(sD1)));--(MODE(1) and sD2) or (not(MODE(1)) and not(sD2));
sortie(1) <=((MODE(1) and sD2) or (not(MODE(1)) and not(sD2)));
sortie(2) <=((MODE(1) and sD3) or (not(MODE(1)) and not(sD3)));
sortie(3) <=((MODE(1) and sD4) or (not(MODE(1)) and not(sD4)));
    
end Behavioral;
