----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/28/2023 09:15:13 PM
-- Design Name: 
-- Module Name: compteur - Behavioral
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity compteur is
    Port ( clk_timer : in STD_LOGIC;
           Out_timer : out STD_LOGIC);
end compteur;

architecture Behavioral of compteur is

signal s_compt_sortie : unsigned(24 DOWNTO 0) := "0000000000000000000000000";

begin

PROCESS (clk_timer)
BEGIN
IF clk_timer'EVENT AND clk_timer = '1' THEN
IF s_compt_sortie >= "1111111111111111111100000" THEN
Out_timer <= '1';
s_compt_sortie <= "0000000000000000000000000";
ELSE
Out_timer <= '0';
s_compt_sortie <= s_compt_sortie + 1;
END IF;
END IF;
END PROCESS;

end Behavioral;
