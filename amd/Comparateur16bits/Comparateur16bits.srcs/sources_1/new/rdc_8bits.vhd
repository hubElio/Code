----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/29/2023 09:49:24 AM
-- Design Name: 
-- Module Name: Registre_decalage_combinatoire - Behavioral
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

entity rdc_8bits is
    Port ( RESET : in STD_LOGIC;
           CLK : in STD_LOGIC;
           INPUT : in STD_LOGIC;
           ENABLE : in STD_LOGIC;
           OUTPUT : out STD_LOGIC_VECTOR (9 downto 0));
end rdc_8bits;

architecture Behavioral of rdc_8bits is

component compteur
    Port ( clk_compteur : in STD_LOGIC;
           reset_compteur : in STD_LOGIC;
           clkout_compteur : out STD_LOGIC);
end component;

component bascule_reset_a_0
Port ( reset_bascule_reset_a_0 : in STD_LOGIC;
           en_bascule_reset_a_0 : in STD_LOGIC;
           D_bascule_reset_a_0 : in STD_LOGIC;
           Q_bascule_reset_a_0 : out STD_LOGIC;
           clk_bascule_reset_a_0 : in STD_LOGIC);
end component;



signal se,clkout : STD_LOGIC;
signal sD1,sD2,sD3,sD4,sD5,sD6,sD7,sD8,sD9,sD10,sQ1,sQ2,sQ3,sQ4,sQ5,sQ6,sQ7,sQ8,sQ9,sQ10 : STD_LOGIC;

begin

Compteur_i : compteur port map(clk,reset,clkout);

bascule_reset_a_0_i_1 : bascule_reset_a_0 port map(Reset,ENABLE,sD1,sQ1,clkout);
bascule_reset_a_0_i_2 : bascule_reset_a_0 port map(Reset,ENABLE,sD2,sQ2,clkout);
bascule_reset_a_0_i_3 : bascule_reset_a_0 port map(Reset,ENABLE,sD3,sQ3,clkout);
bascule_reset_a_0_i_4 : bascule_reset_a_0 port map(Reset,ENABLE,sD4,sQ4,clkout);
bascule_reset_a_0_i_5 : bascule_reset_a_0 port map(Reset,ENABLE,sD5,sQ5,clkout);
bascule_reset_a_0_i_6 : bascule_reset_a_0 port map(Reset,ENABLE,sD6,sQ6,clkout);
bascule_reset_a_0_i_7 : bascule_reset_a_0 port map(Reset,ENABLE,sD7,sQ7,clkout);
bascule_reset_a_0_i_8 : bascule_reset_a_0 port map(Reset,ENABLE,sD8,sQ8,clkout);
bascule_reset_a_0_i_9 : bascule_reset_a_0 port map(Reset,ENABLE,sD9,sQ9,clkout);
bascule_reset_a_0_i_10 : bascule_reset_a_0 port map(Reset,ENABLE,sD10,sQ10,clkout);


sD1 <= ((ENABLE and INPUT) or (not(ENABLE) and sD10));
sD2 <= sQ1;
sD3 <= sQ2;
sD4 <= sQ3;
sD5 <= sQ4;
sD6 <= sQ5;
sD7 <= sQ6;
sD8 <= sQ7;
sD9 <= sQ8;
sD10 <= sQ9;

OUTPUT(0) <= sD1;
OUTPUT(1) <= sD2;
OUTPUT(2) <= sD3;
OUTPUT(3) <= sD4;
OUTPUT(4) <= sD5;
OUTPUT(5) <= sD6;
OUTPUT(6) <= sD7;
OUTPUT(7) <= sD8;
OUTPUT(8) <= sD9;
OUTPUT(9) <= sD10;


end Behavioral;
