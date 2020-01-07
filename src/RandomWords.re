let getSingle = () => Words.all[Random.int(Array.length(Words.all))];

let rec getMultiple = (~count) => {
  let words = [||];

  if (count <= 0) {
    words;
  } else {
    Array.append(
      Array.append(words, [|getSingle()|]),
      getMultiple(~count=count - 1),
    );
  };
};