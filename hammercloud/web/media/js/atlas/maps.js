function generateTableCloud(items, metric, cloud) {

	var SIZE = parseInt(items.length / 5 * 4);
	
	if (SIZE == 0) {
		SIZE = 1;
	}

	var toWrite = new Array(SIZE);
	var toCount = new Array(SIZE);

	var TABLE_WIDTH = 15;

	for (i = 0; i < toWrite.length; i++) {
		toWrite[i] = new Array(TABLE_WIDTH);
		toCount[i] = new Array(TABLE_WIDTH);
	}

	length = [ 3, 3, 3, 4 ];
	height = [ 1, 1, 1, 2 ];
	colors = [ 'ongrey', 'ongreen', 'onyellow', 'onred' ];

	var myTable = $('#centerbar');
	myTable.append('<h4 id="c' + cloud + '">' + cloud + '</h4>');
	myTable.append('<table id="map_' + cloud + '" class="map"></table>');
	myTable = $('#centerbar > table:last');

	for (s = 0; s < items.length; s++) {
		if (items[s][1] < 0.0) {
			lhc = 0;
		} else if (items[s][1] = 0.0) {
			lhc = 3;
		} else if (items[s][1] < 0.5) {
			lhc = 2;
		} else {
			lhc = 1;
		}

		lock = -1;
		y = -1;
		x = 0;

		while (lock != 0) {

			y += 1;

			for (i = 0; i < TABLE_WIDTH; i++) {

				dance:

				if (i + length[lhc] < TABLE_WIDTH + 1) {

					for (h = 0; h < height[lhc]; h++) {
						for (l = 0; l < length[lhc]; l++) {
							if (toCount[y + h][i + l] == 1) {
								break dance;
							}// end if
						}// end for l
					}// end for h

					if (lock == -1) {
						x = i;
						lock = 0;
						break;
					}
				}// end if < 13
			}// end for i

		}// end while

		for (j = y; j < y + height[lhc]; j++) {
			for (i = x; i < x + length[lhc]; i++) {
				toCount[j][i] = 1;
			}// end for i
		}// end for j
		toWrite[y][x] = [ length[lhc], height[lhc], colors[lhc], items[s] ];

	}

	for (y = 0; y < toWrite.length; y++) {

		var row = document.createElement("tr");

		for (x = 0; x < toWrite[y].length; x++) {

			var cell = document.createElement("td");
			if (toWrite[y][x]) {

				var message = toWrite[y][x][3][0];
				if (message.length > 15) {
					message = message.slice(0, 14) + '...';
				}

				customMsg = 'No test yesterday.';
				if (toWrite[y][x][2] != 'ongrey'
						&& toWrite[y][x][2] != 'onblue') {
					customMsg = "<p>" + metric + " " + toWrite[y][x][3][1]
							+ "</p>";
				} else if (toWrite[y][x][2] == 'onblue') {
					customMsg = 'No concluded jobs yesterday.';
				}

				cell.innerHTML = message + "<span class='map_legend'><h3>"
						+ toWrite[y][x][3][0] + "</h3>" + customMsg + "</span>";
				cell.setAttribute("rowspan", toWrite[y][x][1]);
				cell.setAttribute("colspan", toWrite[y][x][0]);
				cell.setAttribute("class", toWrite[y][x][2]);
				cell.setAttribute("onclick", "DoNav('" + toWrite[y][x][3][2]
						+ "');")
				cell.style.width = '120px';
				row.appendChild(cell);
			}
		}

		myTable.append(row);

	}
}

function generateTablesBackend(items, metric, backend) {
	var myTable = $('#centerbar');
	//myTable.empty();
	myTable.append('<h2 id="b' + backend + '"style="text-decoration:underline">' + backend + '</h2>');

	for (i in items) {
		if (items[i].length > 0) { 
			generateTableCloud(items[i], metric, i);
		}
	}
}
