function clearBoard(){
	for (var i = 0; i < board.length; i++){
		for (var j = 0; j < board[i].length; j++){
			board[i][j] = 0;
		}
	}
}


(function() {
	'user strict';

	describe('Test gameOfLive.js', function() {
		before(function() {
			initVariable(100, 100, 20, 0.7, 10);
			initConst();
		});

		describe('Test initVariable', function() {
			it('should init several data correctly', function() {
				assert.equal(canvas.width, 100);
				assert.equal(canvas.height, 100);
				assert.equal(numCellW, 5);
				assert.equal(numCellH, 5);
				assert.equal(cellSize, 20);
				assert.equal(cellDensity, 0.7);
				assert.equal(refreshRate, 10);
			});
		});

		describe('Test initBoard', function() {
			it('should init board correctly, either 0 or 1', function() {
				var cellNum = 0, deathNum = 0;
				for (var k = 0; k < 10; k++){
					try{
						board.splice(0, board.length);
					}
					catch (e){}
					initBoard();
					assert.equal(board.length, 5);
					assert.equal(board[0].length, 5);
					for (var i = 0; i < 5; i++){
						for (var j = 0; j < 5; j++){
							if (board[i][j] === 1){
								cellNum++;
							}
							else if (board[i][j] === 0){
								deathNum++;
							}
						}
					}
				}
				var rate = cellNum / 250;
				assert.equal(deathNum + cellNum, 250);
				assert.equal((rate > 0.6 && rate < 0.8), true);
			});
		});

		describe('Test transform', function() {
			it('should transform state correctly', function() {
				clearBoard();
				board[0][0] = 1; board[0][3] = 2; board[0][4] = 1;
				board[2][0] = 1; board[3][0] = 1; board[4][0] = 2;
				transform();
				assert.deepEqual(board[0], [1, 0, 0, 2, 0]);
				assert.deepEqual(board[1], [1, 0, 0, 0, 0]);
				assert.deepEqual(board[2], [1, 0, 0, 0, 0]);
				assert.deepEqual(board[3], [1, 0, 0, 0, 0]);
				assert.deepEqual(board[4], [2, 0, 0, 0, 0]);

				clearBoard();
				board[0] = [1, 1, 1, 1, 1]; board[1] = [1, 1, 1, 1, 1];
				board[2] = [1, 1, 1, 1, 1]; board[3] = [1, 1, 1, 1, 1];
				board[4] = [1, 1, 1, 1, 1];
				transform();
				assert.deepEqual(board[0], [0, 0, 0, 0, 0]);
				assert.deepEqual(board[1], [0, 0, 0, 0, 0]);
				assert.deepEqual(board[2], [0, 0, 0, 0, 0]);
				assert.deepEqual(board[3], [0, 0, 0, 0, 0]);
				assert.deepEqual(board[4], [0, 0, 0, 0, 0]);

			});
		});

		describe('Test paint', function() {
			it('should draw correctly', function() {
				clearBoard();
				board[0] = [0, 0, 0, 0, 0];
				board[1] = [1, 1, 1, 1, 1];
				board[2] = [2, 2, 2, 2, 2];
				//board[0]= [1, 0, 0, 2, 0];
				//board[1]= [1, 0, 0, 0, 0];
				//board[2]= [1, 0, 0, 0, 0];
				//board[3]= [1, 0, 0, 0, 0];
				//board[4]= [2, 0, 0, 0, 0];
				paint();
				var data = ctx.getImageData(0, 0, 100, 100).data;
				var i, j, x, y, z;
				i = 0;
				for (j = 0; j < 5; j++){
					x = i * cellSize + cellSize / 2;
					y = j * cellSize + cellSize / 2;
					z = (y * 100 + x) * 4;
					assert.equal(data[z + 0], 255);
					assert.equal(data[z + 1], 255);
					assert.equal(data[z + 2], 255);
				}
				i = 1;
				for (j = 0; j < 5; j++){
					x = i * cellSize + cellSize / 2;
					y = j * cellSize + cellSize / 2;
					z = (y * 100 + x) * 4;
					assert.equal(data[z + 0], 173);
					assert.equal(data[z + 1], 216);
					assert.equal(data[z + 2], 230);
				}
				i = 2;
				for (j = 0; j < 5; j++){
					x = i * cellSize + cellSize / 2;
					y = j * cellSize + cellSize / 2;
					z = (y * 100 + x) * 4;
					assert.equal(data[z + 0], 0);
					assert.equal(data[z + 1], 0);
					assert.equal(data[z + 2], 0);
				}
			});
		});
	});
})();