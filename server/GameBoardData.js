
/**
 * This class will store the game state of a players board on the server.
 * This class will store current guesses and ship positions
 */

require("GameShipData");
require("./utilities");

let GameBoardData = class{

    constructor(shipArray){
        /**
         * @param {Array[GameShipData]} - Contains all of the ships to the board.
         */
        this._guesses = new Array();
        this._remainingShips = shipArray;
        this._sunkShip = new Array();
    }

    /**
     * Make a guess on the board
     * @param {Int} x - x coordinate of the guess
     * @param {Int} y - y coordinate of the guess
     * @modify - Make the ship as sunken/hit if the guess succeed
     * @return {Guesses} - Returns whether the guess is a hit/miss/sink.
     */
    guess(x, y){
        this._guesses.push(new Coordinate(x, y));

        for (let i = 0; i < this._remainingShips.length; i++){
            ship = this._remainingShips[i];
            classification = ship.guess(x, y)
            if (classification == Guesses.HIT){
                return Guesses.HIT;

            }
            else if (classification == Guesses.SINK){
                this._remainingShips.splice(i, 1);
                this._sunkShip.push(ship);
                return Guesses.SINK;
            }
        }
        return Guesses.MISS;
    }

    /**
    * Return the number of ships remaining.
    * 
    * @return {Int} - Corresponds to the number of ships on the board.
    */
    get shipCount(){
        
        return this._remainingShips.length;
    }


    /**
    * Returns the ID of the last sunk simp
    * 
    * @return {Int} - Returns the id of the last sunk ship. Return null if no ship sunk.
    */
    get lastSunkID(){
        if (this._sunkShip.length == 0){
            return null;
        }
        return this._sunkShip[this._sunkShip.length - 1].id;
    }
}