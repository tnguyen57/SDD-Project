

let miscFunctions = class{
    /**
     * Create an array of coordinates corresponding to a ship.
     * @size - The size of the ship
     * @start - The coordinate of the top-left position of the ship
     * @orientation - An integer. 1 means it's vertical. Anything else is horizontal.
     */
    static generateShip(size, start, orientation){
        let ship = [];
        for (let i = 0; i < size; i++){
            if (orientation === 1){
                ship.push({x: start.x, y: start.y + i});
            }
            else{
                ship.push({x: start.x + i, y: start.y});
            }
        }
        return ship;
    }

    /**
     * Generates and return a random integer between 
     * min (inclusive and max (exlucisve)
     * 
     * @param {Int} min - The lower inclusive bound of the  random integer generator
     * @param {Int} max - The upper exclusive bound of the  random integer generator
     * @return {Int} - The randomly generated integer between min (inclusive) and max (exclusive)
     */
    static getRndInteger(min, max) {
        return Math.floor(Math.random() * (max - min) ) + min;
    }

}

module.exports = miscFunctions;