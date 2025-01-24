----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/25/2023 02:34:43 PM
-- Design Name: 
-- Module Name: ADD_4bits - Behavioral
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

entity ADD_7bits is
    Port ( 
           clk : in STD_LOGIC;
           en : in STD_LOGIC;
           reset : in STD_LOGIC;
           S : out STD_LOGIC
           );
end ADD_7bits;

architecture Behavioral of ADD_7bits is

component ADD_2bits
    Port ( A : in STD_LOGIC;
           B : in STD_LOGIC;
           Ci : in STD_LOGIC;
           Co : out STD_LOGIC;
           S : out STD_LOGIC);
end component;

component bascule_reset_a_1
    Port ( reset_bascule_reset_a_1 : in STD_LOGIC;
           en_bascule_reset_a_1 : in STD_LOGIC;
           D_bascule_reset_a_1 : in STD_LOGIC;
           Q_bascule_reset_a_1 : out STD_LOGIC;
           clk_bascule_reset_a_1 : in STD_LOGIC);
end component;

component bascule_reset_a_0 is
    Port ( reset_bascule_reset_a_0 : in STD_LOGIC;
           en_bascule_reset_a_0 : in STD_LOGIC;
           D_bascule_reset_a_0 : in STD_LOGIC;
           Q_bascule_reset_a_0 : out STD_LOGIC;
           clk_bascule_reset_a_0 : in STD_LOGIC);
end component;

component compteur
    Port ( clk_compteur : in STD_LOGIC;
           reset_compteur : in STD_LOGIC;
           clkout_compteur : out STD_LOGIC);
end component;



signal c1,c2,c3,c4,c5,c6,c7,c8,c9,sen_bascule,sclk_bascule,clkout_compteur: STD_LOGIC := '0';
signal sreset_bascule: STD_LOGIC := '1';
signal sQ_bascule: STD_LOGIC_VECTOR(6 downto 0) := "0000000";
signal sD_bascule : STD_LOGIC_VECTOR(6 downto 0);

begin
compteur_i : compteur port map(clk,
           sreset_bascule,
           clkout_compteur);

ADD_2bits_i_1 : ADD_2bits port map('1',sQ_bascule(0),'0',c1,sD_bascule(0));
ADD_2bits_i_2 : ADD_2bits port map('0',sQ_bascule(1),c1,c2,sD_bascule(1));
ADD_2bits_i_3 : ADD_2bits port map('1',sQ_bascule(2),c2,c3,sD_bascule(2));
ADD_2bits_i_4 : ADD_2bits port map('1',sQ_bascule(3),c3,c4,sD_bascule(3));
ADD_2bits_i_5 : ADD_2bits port map('1',sQ_bascule(4),c4,c5,sD_bascule(4));
ADD_2bits_i_6 : ADD_2bits port map('1',sQ_bascule(5),c5,c6,sD_bascule(5));
ADD_2bits_i_7 : ADD_2bits port map('1',sQ_bascule(6),c6,c7,sD_bascule(6));


bascule_i_1 : bascule_reset_a_0 port map(sreset_bascule,sen_bascule,sD_bascule(0),sQ_bascule(0),clkout_compteur);
bascule_i_2 : bascule_reset_a_0 port map(sreset_bascule,sen_bascule,sD_bascule(1),sQ_bascule(1),clkout_compteur);
bascule_i_3 : bascule_reset_a_0 port map(sreset_bascule,sen_bascule,sD_bascule(2),sQ_bascule(2),clkout_compteur);
bascule_i_4 : bascule_reset_a_1 port map(sreset_bascule,sen_bascule,sD_bascule(3),sQ_bascule(3),clkout_compteur);
bascule_i_5 : bascule_reset_a_1 port map(sreset_bascule,sen_bascule,sD_bascule(4),sQ_bascule(4),clkout_compteur);
bascule_i_6 : bascule_reset_a_0 port map(sreset_bascule,sen_bascule,sD_bascule(5),sQ_bascule(5),clkout_compteur);
bascule_i_7 : bascule_reset_a_0 port map(sreset_bascule,sen_bascule,sD_bascule(6),sQ_bascule(6),clkout_compteur);

S <= sQ_bascule(6);
sen_bascule <= en;
sreset_bascule <= reset;

end Behavioral;
