type state = {
  attemptedWord: string,
  score: int,
  words: array(string),
};

type action =
  | Change(string);

let component = ReasonReact.reducerComponent("App");

let allWords = [|"Hello", "Every", "World"|];

let filterWords = (~attemptedWord, ~words) =>
  Belt.Array.keep(words, word => word != attemptedWord);

let renderWords = wordsArray =>
  Array.map(word => <div> {ReasonReact.string(word)} </div>, wordsArray);

let make = _children => {
  ...component,

  initialState: () => {attemptedWord: "", score: 0, words: allWords},

  reducer: action =>
    switch (action) {
    | Change(attemptedWord) => (
        state => {
          let {words, score} = state;
          let filtered = filterWords(~attemptedWord, ~words);
          let isCorrect = Array.length(filtered) < Array.length(words);

          ReasonReact.Update({
            attemptedWord: isCorrect ? "" : attemptedWord,
            words: filtered,
            score: isCorrect ? score + 1 : score,
          });
        }
      )
    },

  render: ({state: {score, words, attemptedWord}, send}) =>
    <div>
      <div> {ReasonReact.string(string_of_int(score))} </div>
      <div> ...{renderWords(words)} </div>
      <input
        type_="text"
        value=attemptedWord
        onChange={event =>
          send(Change(ReactEvent.Form.target(event)##value))
        }
      />
    </div>,
};