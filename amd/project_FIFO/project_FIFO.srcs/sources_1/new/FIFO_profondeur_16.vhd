----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/29/2023 11:20:28 AM
-- Design Name: 
-- Module Name: FIFO_profondeur_16 - Behavioral
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

entity FIFO_profondeur_16 is
    Port ( FIFO_in : in STD_LOGIC_VECTOR (7 downto 0);
           FIFO_out : out STD_LOGIC_VECTOR (7 downto 0);
           FIFO_we : in STD_LOGIC; -- write enable
           FIFO_re : in STD_LOGIC; -- read enable
           CLK : in STD_LOGIC);
end FIFO_profondeur_16;

architecture Behavioral of FIFO_profondeur_16 is


type FIFO_ARRAY is array (0 to 16 ) of std_logic_vector (7 downto 0);

signal FIFO: FIFO_ARRAY; 
   
   signal counter: unsigned(3 downto 0) := (others =>'0');
begin


end Behavioral;
