type state = {
  attemptedWord: string,
  score: int,
  words: array(string),
  isFinished: bool,
};

type action =
  | Change(string)
  | FinishGame;

let component = ReasonReact.reducerComponent("App");

let allWords = RandomWords.getMultiple(~count=7);

let filterWords = (~attemptedWord, ~words) =>
  Belt.Array.keep(words, word => word != attemptedWord);

let renderWords = wordsArray =>
  Array.map(
    word => <span> {ReasonReact.string(word ++ " ")} </span>,
    wordsArray,
  );

let make = _children => {
  ...component,

  initialState: () => {
    attemptedWord: "",
    score: 0,
    words: allWords,
    isFinished: false,
  },

  reducer: action =>
    switch (action) {
    | FinishGame => (
        state => {
          Js.log("Finished with score: " ++ string_of_int(state.score));

          ReasonReact.Update({...state, isFinished: true});
        }
      )
    | Change(attemptedWord) => (
        state => {
          let {words, score} = state;
          let filtered = filterWords(~attemptedWord, ~words);
          let isCorrect = Array.length(filtered) < Array.length(words);

          ReasonReact.Update({
            ...state,
            attemptedWord: isCorrect ? "" : attemptedWord,
            words: filtered,
            score: isCorrect ? score + 1 : score,
          });
        }
      )
    },

  render: ({state: {score, words, attemptedWord, isFinished}, send}) =>
    <div>
      <Counter onFinish={() => send(FinishGame)} />
      <div> {ReasonReact.string("Score: " ++ string_of_int(score))} </div>
      <div> ...{renderWords(words)} </div>
      <input
        type_="text"
        value=attemptedWord
        disabled=isFinished
        onChange={event =>
          send(Change(ReactEvent.Form.target(event)##value))
        }
      />
    </div>,
};