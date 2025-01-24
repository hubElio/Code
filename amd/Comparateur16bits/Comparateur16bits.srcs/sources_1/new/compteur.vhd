----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/25/2023 01:10:43 PM
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
    Port ( clk_compteur : in STD_LOGIC;
           reset_compteur : in STD_LOGIC;
           clkout_compteur : out STD_LOGIC);
end compteur;

architecture Behavioral of compteur is

signal clk_int : unsigned(25 downto 0):=(others=>'0');

begin

Process(clk_compteur,reset_compteur)
begin
if(reset_compteur='1') then
    clk_int <= (others=>'0');
elsif(clk_compteur'event and clk_compteur = '1') then
   clk_int <= clk_int + 1;
end if;
end process;
--clkout_compteur <= clk_int(22);
clkout_compteur <= clk_int(25);

end Behavioral;
