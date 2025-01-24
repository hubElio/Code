----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/27/2023 07:13:44 PM
-- Design Name: 
-- Module Name: Registre1bit - Behavioral
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

entity bascule is
    Port ( reset : in STD_LOGIC;
           en : in STD_LOGIC;
           D : in STD_LOGIC;
           clk : in STD_LOGIC;
           Q : out STD_LOGIC);
end bascule;

architecture Behavioral of bascule is

signal temp : std_logic :='0';

begin

Q <=temp;

process(reset,en,clk,D)
begin
if(reset = '1')then
    temp <='0';
elsif(clk'event and clk = '1') then
    if(en = '1') then
    temp <= D;
    else
    temp <=temp;
    end if;
end if;
end process;


end Behavioral;
