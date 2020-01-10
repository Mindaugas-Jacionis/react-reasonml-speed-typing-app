module Styles = {
  let container =
    ReactDOMRe.Style.make(
      ~position="relative",
      ~fontFamily="monospace",
      ~fontSize="18px",
      ~lineHeight="24px",
      ~padding="0px 100px",
      (),
    );
  let input =
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~top="0",
      ~left="0",
      ~width="100vw",
      ~height="100vh",
      ~border="none",
      ~background="transparent",
      ~outline="none",
      ~caretColor="transparent",
      ~color="transparent",
      (),
    );
  let board = ReactDOMRe.Style.make(~textAlign="center", ());
  let attemptedWord =
    ReactDOMRe.Style.make(
      ~padding="20px 0 ",
      ~margin="0 auto",
      ~lineHeight="18px",
      (),
    );
  // ToDo: add animation
  let blinkingCursor =
    ReactDOMRe.Style.make(
      ~padding="20px 0 ",
      ~margin="0 auto",
      ~lineHeight="18px",
      ~color="#1f1f1f",
      (),
    );
};

type state = {
  attemptedWord: string,
  score: int,
  words: array(string),
  isFinished: bool,
  attempted: bool,
};

type action =
  | Change(string)
  | FinishGame;

let component = ReasonReact.reducerComponent("App");

let allWords = RandomWords.getMultiple(~count=200);

let make = _children => {
  ...component,

  initialState: () => {
    attemptedWord: "",
    attempted: false,
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
          let filtered = Belt.Array.keep(words, word => word != attemptedWord);
          let isCorrect = Array.length(filtered) < Array.length(words);

          ReasonReact.Update({
            ...state,
            attemptedWord: isCorrect ? "" : attemptedWord,
            words: filtered,
            score: isCorrect ? score + 1 : score,
            attempted: state.attempted || String.length(attemptedWord) > 0,
          });
        }
      )
    },

  render:
    ({state: {score, words, attempted, attemptedWord, isFinished}, send}) =>
    <div style=Styles.container>
      <input
        autoComplete="off"
        spellCheck=false
        style=Styles.input
        type_="text"
        autoFocus=true
        value=attemptedWord
        disabled=isFinished
        onChange={event =>
          send(Change(ReactEvent.Form.target(event)##value))
        }
      />
      <div style=Styles.board>
        {String.length(attemptedWord) > 0 ?
           <p style=Styles.attemptedWord>
             {ReasonReact.string(attemptedWord)}
           </p> :
           <p style=Styles.blinkingCursor> {ReasonReact.string("|")} </p>}
        <Counter shouldCount=attempted onFinish={() => send(FinishGame)} />
        <Score value=score />
        <TextView words />
      </div>
    </div>,
};