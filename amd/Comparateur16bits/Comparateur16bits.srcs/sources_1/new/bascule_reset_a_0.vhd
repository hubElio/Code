----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/29/2023 09:39:41 AM
-- Design Name: 
-- Module Name: bascule_reset_a_0 - Behavioral
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

entity bascule_reset_a_0 is
Port ( reset_bascule_reset_a_0 : in STD_LOGIC;
           en_bascule_reset_a_0 : in STD_LOGIC;
           D_bascule_reset_a_0 : in STD_LOGIC;
           Q_bascule_reset_a_0 : out STD_LOGIC;
           clk_bascule_reset_a_0 : in STD_LOGIC);
end bascule_reset_a_0;

architecture Behavioral of bascule_reset_a_0 is

signal temp : std_logic := '0';

begin
Q_bascule_reset_a_0 <= temp;

process(reset_bascule_reset_a_0,en_bascule_reset_a_0,D_bascule_reset_a_0,clk_bascule_reset_a_0)

begin
if(reset_bascule_reset_a_0 = '1') then
    temp <= '0';
elsif(clk_bascule_reset_a_0'event and clk_bascule_reset_a_0 = '1') then
    if(en_bascule_reset_a_0 = '1') then
        temp <= D_bascule_reset_a_0;
    else
        temp <= temp;
    end if;
end if;
end process;


end Behavioral;
